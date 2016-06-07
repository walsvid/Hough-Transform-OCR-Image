//
// Created by wen on 16/6/6.
//

#ifndef HOUGH_TRANSFORM_OCR_IMAGE_TOOLS_H
#define HOUGH_TRANSFORM_OCR_IMAGE_TOOLS_H

#include <opencv2/opencv.hpp>
#include <vector>

class Tools {
public:
    Tools();

    ~Tools();

    static void mergeLines(std::vector<cv::Vec4i> &lines, cv::Vec4i &edge, int type);

    static cv::Point crossPoint(cv::Vec4i const &line1, cv::Vec4i const &line2);

private:
    static void mergeHorizontalLines(std::vector<cv::Vec4i> &lines, cv::Vec4i &edge);

    static void mergeVerticalLines(std::vector<cv::Vec4i> &lines, cv::Vec4i &edge);
};

#endif //HOUGH_TRANSFORM_OCR_IMAGE_TOOLS_H
