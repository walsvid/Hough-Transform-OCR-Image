//
// Created by wen on 16/6/6.
//

#include "Tools.h"

Tools::Tools() { }

Tools::~Tools() { }

void Tools::mergeLines(std::vector<cv::Vec4i> &lines, cv::Vec4i &edge, int type) {
    if (type == 1)
        mergeVerticalLines(lines, edge);
    else
        mergeHorizontalLines(lines, edge);
}

cv::Point Tools::crossPoint(cv::Vec4i const &line1, cv::Vec4i const &line2) {
    cv::Point p;
    float denominator = (line1[1] - line1[3]) * (line2[2] - line2[0]) - (line1[2] - line1[0]) * (line2[1] - line2[3]);
    p.x = (line1[1] * line1[2] - line1[0] * line1[3]) * (line2[2] - line2[0]) -
          (line1[2] - line1[0]) * (line2[1] * line2[2] - line2[0] * line2[3]);
    p.x = (int) (p.x / denominator);
    p.y = (line1[1] - line1[3]) * (line2[1] * line2[2] - line2[0] * line2[3]) -
          (line2[1] - line2[3]) * (line1[1] * line1[2] - line1[0] * line1[3]);
    p.y = (int) (p.y / denominator);
    return p;
}

void Tools::mergeHorizontalLines(std::vector<cv::Vec4i> &lines, cv::Vec4i &edge) {
    auto distancePowerFromVec4i = [](cv::Vec4i &line1) {
        return (pow(abs(line1[0] - line1[2]), 2) + pow(abs(line1[1] - line1[3]), 2));
    };
    double dis = 0.0;
    for (size_t i = 0; i < lines.size(); ++i) {
        double tmpDis = 0.0;
        if ((tmpDis = distancePowerFromVec4i(lines[i])) > dis) {
            dis = tmpDis;
            edge = lines[i];
        }
    }
}

void Tools::mergeVerticalLines(std::vector<cv::Vec4i> &lines, cv::Vec4i &edge) {
    std::vector<cv::Vec4i> tmplines(lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        cv::Vec4i line = lines[i];
        std::swap(line[0], line[1]);
        std::swap(line[2], line[3]);
        tmplines.emplace_back(line);
    }
    mergeHorizontalLines(tmplines, edge);
    std::swap(edge[0], edge[1]);
    std::swap(edge[2], edge[3]);
}