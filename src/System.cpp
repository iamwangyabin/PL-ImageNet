//
// Created by wang on 19-2-27.
//

#include <opencv2/opencv.hpp>
#include "System.h"

//void init_system(){
//    std::vector<cv::Point2f> p1,p2;
//    std::vector<cv::Vec3b> c2;
//
//    cv::Mat R,T;
//    cv::Mat mask;
//    cv::findTransform()
//}

void reconstruct(
        cv::Mat& K,
        cv::Mat& R,
        cv::Mat& T,
        std::vector<cv::Point2f>& p1,
        std::vector<cv::Point2f>& p2,
        std::vector<cv::Point3d>& points
        ){
    cv::Mat structure;

    //  两相机投影矩阵
    cv::Mat proj1(3,4,CV_32FC1);
    cv::Mat proj2(3,4,CV_32FC1);
    std::cout<<"ok"<<std::endl;
    proj1(cv::Range(0,3),cv::Range(0,3))=cv::Mat::eye(3,3,CV_32FC1);
    proj1.col(3) = cv::Mat::zeros(3, 1, CV_32FC1);
    std::cout<<"ok"<<std::endl;
    R.convertTo(proj2(cv::Range(0, 3), cv::Range(0, 3)), CV_32FC1);
    T.convertTo(proj2.col(3), CV_32FC1);
    std::cout<<"ok"<<std::endl;
    std::cout<<R<<std::endl;
    cv::Mat fK;
    K.convertTo(fK,CV_32FC1);
    proj1=fK*proj1;
    proj2=fK*proj2;
    std::cout<<"ok"<<std::endl;
    cv::triangulatePoints(proj1,proj2,p1,p2,structure);
    std::cout<<"ok"<<std::endl;
    for (int i = 0; i < structure.cols; ++i) {
        cv::Mat x=structure.col(i);
        x/=x.at<float>(3);
        cv::Point3d p(
                x.at<float>(0),
                x.at<float>(1),
                x.at<float>(2)
        );
        points.push_back(p);
    }
}