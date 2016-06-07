//
// Created by wen on 16/6/6.
//

#ifndef HOUGH_TRANSFORM_OCR_IMAGE_HOUGHDETECTEDGE_H
#define HOUGH_TRANSFORM_OCR_IMAGE_HOUGHDETECTEDGE_H

#include "DetectEdge.h"

class HoughDetectEdge : public DetectEdge {
public:
    HoughDetectEdge();

    virtual ~HoughDetectEdge();

    virtual void detect(cv::Mat &image, std::vector<cv::Vec4i> &edges);

    virtual bool detect(cv::Mat &image, cv::Mat &dst) = 0;

protected:
    void canndyImage(cv::Mat &gray);

    void houghLines(cv::Mat &gray, std::vector<std::vector<cv::Vec4i>> &lines);

    void mergeLines(std::vector<std::vector<cv::Vec4i>> &lines, std::vector<cv::Vec4i> &edges);

};

#endif //HOUGH_TRANSFORM_OCR_IMAGE_HOUGHDETECTEDGE_H
