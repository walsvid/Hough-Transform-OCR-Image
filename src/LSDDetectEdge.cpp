//
// Created by wen on 16/6/6.
//

#include "LSDDetectEdge.h"
#include "Tools.h"


LSDDetectEdge::LSDDetectEdge() {
    detector_ = cv::createLineSegmentDetector(cv::LSD_REFINE_NONE, 0.8, 0.6, 4.0, 20);
}


LSDDetectEdge::~LSDDetectEdge() {
}

void LSDDetectEdge::detect(cv::Mat &image, std::vector<cv::Vec4i> &edges) {
    edges.clear();
    cv::Mat gray;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray, CV_BGR2GRAY);
    }
    else {
        gray = image.clone();
    }
    std::vector<std::vector<cv::Vec4i>> lines;
    LSDLines(gray, lines);
    if (lines.size() != 4) return;
    //merge lines
    mergeLines(lines, edges);

}

bool LSDDetectEdge::detect(cv::Mat &image, cv::Mat &dst) {
    std::vector<cv::Vec4i> edges;
    detect(image, edges);

    if (edges.size() != 4) {
        std::cerr << "detection error " << std::endl;
        return false;
    }
    std::vector<cv::Point2f> PTransfrom(4);
    std::vector<cv::Point2f> PTransto(4);
    PTransfrom[0] = Tools::crossPoint(edges[0], edges[2]); //upleft
    PTransfrom[1] = Tools::crossPoint(edges[0], edges[3]); //upright
    PTransfrom[2] = Tools::crossPoint(edges[1], edges[2]); //downleft
    PTransfrom[3] = Tools::crossPoint(edges[1], edges[3]); //downright
#ifdef _DEBUG
    for (size_t i = 0; i < PTransfrom.size(); ++i)
    {
        cv::circle(image, PTransfrom[i], 2, cv::Scalar(0, 0, 255),2);
    }
    cv::imshow("point", image);
    cv::imwrite("../output/point.jpg", image);
    cv::waitKey();
#endif //end _DEBUG
    PTransto[0].x = 0;
    PTransto[0].y = 0;
    PTransto[1].x = 640;
    PTransto[1].y = 0;
    PTransto[2].x = 0;
    PTransto[2].y = 404;
    PTransto[3].x = 640;
    PTransto[3].y = 404;
    cv::Mat tf = cv::getPerspectiveTransform(PTransfrom, PTransto);
    dst = cv::Mat::zeros(cv::Size(640, 404), image.type());
    cv::warpPerspective(image, dst, tf, dst.size(), cv::INTER_CUBIC);
#ifdef _DEBUG
    cv::imshow("result", dst);
    cv::imwrite("../output/result.jpg", dst);
    cv::waitKey();
#endif //end _DEBUG

    return true;

}

void LSDDetectEdge::LSDLines(cv::Mat &gray, std::vector<std::vector<cv::Vec4i>> &lines) {
    const double THETA = 35.0 / 180;
    const int LINENUM = 8;
    lines.clear();
    std::vector<cv::Vec4i> tmplines;
    detector_->detect(gray, tmplines);

    std::vector<cv::Vec4i> ups;
    std::vector<cv::Vec4i> downs;
    std::vector<cv::Vec4i> lefts;
    std::vector<cv::Vec4i> rights;
    for (size_t i = 0; i < tmplines.size(); ++i) {
        cv::Vec4i &line = tmplines[i];
        //cv::line(gray, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(255 * (i <= 1), 0, 255 * (i>1)), 1, CV_AA);
        int detaX = abs(line[0] - line[2]);
        int detaY = abs(line[1] - line[3]);

        if (detaX > detaY && atan(1.0 * detaY / detaX) < THETA)// "水平方向"
        {
            if (std::max(line[1], line[3]) < gray.rows / 3) {
                ups.emplace_back(line);
                continue;
            }
            if (std::max(line[1], line[3]) > gray.rows * 2 / 3) {
                downs.emplace_back(line);
                continue;
            }
        }
        if (detaX < detaY && atan(1.0 * detaX / detaY) < THETA) {
            if (std::max(line[0], line[2]) < gray.cols / 4) {
                lefts.emplace_back(line);
                continue;
            }
            if (std::max(line[0], line[2]) > gray.cols * 3 / 4) {
                rights.emplace_back(line);
                continue;
            }
        }
    }

    auto removeShortLine = [&LINENUM](std::vector<cv::Vec4i> &_lines) {
        if (_lines.size() < LINENUM) return;
        std::vector<cv::Vec4i> _tmplines;
        _tmplines.swap(_lines);
        sort(_tmplines.begin(), _tmplines.end(), [](cv::Vec4i &line1, cv::Vec4i &line2) {
            \
            return (pow(abs(line1[0] - line1[2]), 2) + pow(abs(line1[1] - line1[3]), 2)) > \
            (pow(abs(line2[0] - line2[2]), 2) + pow(abs(line2[1] - line2[3]), 2));
        });
        _lines.insert(_lines.begin(), _tmplines.begin(), _tmplines.begin() + LINENUM);

    };
    removeShortLine(ups);
    lines.emplace_back(ups);
    removeShortLine(downs);
    lines.emplace_back(downs);
    removeShortLine(lefts);
    lines.emplace_back(lefts);
    removeShortLine(rights);
    lines.emplace_back(rights);
    //return  lines.size() == 4;
#ifdef _DEBUG
    cv::Mat cdst;
    cv::cvtColor(gray, cdst, CV_GRAY2BGR);
    for (size_t i = 0; i < lines.size(); ++i)
    {
        for (size_t j = 0; j < lines[i].size(); ++j)
        {
            cv::Vec4i& l = lines[i][j];
            cv::line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255 * (i<=1), 0, 255*(i>1)), 1, CV_AA);
        }
    }

    cv::imshow("lines", cdst);
    cv::imwrite("../output/lines.jpg", cdst);
    cv::waitKey();
#endif //end _DEBUG
}

void LSDDetectEdge::mergeLines(std::vector<std::vector<cv::Vec4i>> &lines, std::vector<cv::Vec4i> &edges) {
    for (size_t i = 0; i < lines.size(); ++i) {
        cv::Vec4i edge;
        Tools::mergeLines(lines[i], edge, static_cast<int>(i >= 2));
        edges.emplace_back(edge);
    }
}
