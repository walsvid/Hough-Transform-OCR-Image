#ifndef HOUGH_TRANSFORM_OCR_IMAGE_DETECTEDGE_H
#define HOUGH_TRANSFORM_OCR_IMAGE_DETECTEDGE_H

#include <opencv2/opencv.hpp>
#include <vector>

class DetectEdge {
public:
    DetectEdge();

    virtual ~DetectEdge();

    virtual void detect(cv::Mat &image, std::vector<cv::Vec4i> &edges) = 0;

    virtual bool detect(cv::Mat &image, cv::Mat &dst) = 0;
};


#endif //HOUGH_TRANSFORM_OCR_IMAGE_DETECTEDGE_H
