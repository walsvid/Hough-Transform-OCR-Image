#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "DetectEdge.h"
#include "LSDDetectEdge.h"

using namespace std;

int main(int argc, char * argv[])
{
    LSDDetectEdge de;


    vector<cv::Vec4i> edges;
    ifstream input("../src/train.txt");
    string imagename;
    while (input >> imagename)
    {
        cv::Mat dst;
        cv::Mat color = cv::imread("../train/" + imagename);
//        cv::imshow("color", color);

        if(!color.data)                         //判断图片调入是否成功
            return -1;                          //调入图片失败则退出

        de.detect(color, dst);

        cv::Rect name(105, 42, 150, 55);
        cv::Rect nums(200, 320, 410, 56);
        cv::rectangle(dst, name, cv::Scalar(0, 0, 255));
        cv::rectangle(dst, nums, cv::Scalar(255, 0, 0));
        cv::imshow("img", dst);
        cv::waitKey();
        cv::destroyAllWindows();
    }

    cv::waitKey();
}