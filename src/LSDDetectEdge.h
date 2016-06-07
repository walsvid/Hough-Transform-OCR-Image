//
// Created by wen on 16/6/6.
//

#ifndef HOUGH_TRANSFORM_OCR_IMAGE_LSDDETECTEDGE_H
#define HOUGH_TRANSFORM_OCR_IMAGE_LSDDETECTEDGE_H

#include <opencv2/opencv.hpp>
#include "DetectEdge.h"

class LSDDetectEdge : public DetectEdge {
public:
    LSDDetectEdge();

    virtual ~LSDDetectEdge();

    virtual void detect(cv::Mat &image, std::vector<cv::Vec4i> &edges);

    virtual bool detect(cv::Mat &image, cv::Mat &dst);

    void LSDLines(cv::Mat &gary, std::vector<std::vector<cv::Vec4i>> &lines);

    void mergeLines(std::vector<std::vector<cv::Vec4i>> &lines, std::vector<cv::Vec4i> &edges);

private:
    cv::Ptr<cv::LineSegmentDetector> detector_;
};

#endif //HOUGH_TRANSFORM_OCR_IMAGE_LSDDETECTEDGE_H
