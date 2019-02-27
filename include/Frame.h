//
// Created by wang on 19-2-26.
//

#ifndef SIMPLESFM_FRAME_H
#define SIMPLESFM_FRAME_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/calib3d.hpp>

class Frame{
public:
    int id;
    cv::Mat img;
    cv::Mat descriptors;
    std::vector<cv::KeyPoint> keypoints;
//    cv::Mat T; // 4x4 位置转换矩阵
//    cv::Mat P; // 3x4 投影矩阵 P[3][4]表示投影矩阵（三维点和投影矩阵相乘得到二维坐标）
    cv::Mat R;
    cv::Mat T;
//    Frame();
    Frame(const cv::Mat &imge,int _id);

    void ExtractSIFT();
    void setPose(cv::Mat Tcw);
    std::vector<cv::DMatch> matchImage(cv::Mat descriptors2);
    bool find_transform(cv::Mat& K, std::vector<cv::Point2f>& p1, std::vector<cv::Point2f>& p2);
private:
    cv::Mat mask;

};

#endif //SIMPLESFM_FRAME_H

