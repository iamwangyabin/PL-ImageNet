//
// Created by wang on 19-2-26.
//

#include <Frame.h>

#include "Frame.h"

void Frame::ExtractSIFT() {
    cv::Mat image;
    cv::GaussianBlur(img,image,cv::Size(3,3),0.5);

    cv::Ptr<cv::Feature2D>f2d = cv::xfeatures2d::SIFT::create();
    f2d->detect(image,keypoints);

    f2d->compute(image,keypoints,descriptors);

}

Frame::Frame(const cv::Mat &imge, int _id) {
    img=imge;
    id=_id;
}

std::vector<cv::DMatch> Frame::matchImage(cv::Mat descriptors2) {
    cv::BFMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors,descriptors2,matches);

    return matches;
}

bool Frame::find_transform(cv::Mat &K, std::vector<cv::Point2f> &p1, std::vector<cv::Point2f> &p2) {
//    std::cout<<"sfad"<<std::endl;

    // 根据内参矩阵获取相机的焦距和光心坐标（主点坐标）
    double focal_length = K.at<double>(0,0);
    cv::Point2d principle_point((K.at<double>(0,2)),K.at<double>(1,2));
//    std::cout<<"sfad"<<std::endl;

    cv::Mat E=cv::findEssentialMat(p1,p2,focal_length,principle_point,cv::RANSAC,0.999,1.0,mask);
//    std::cout<<"sfad"<<std::endl;
    double feasible_count = cv::countNonZero(mask);
    if (feasible_count <= 15 || (feasible_count / p1.size()) < 0.6)
        return false;

    int pass_count = cv::recoverPose(E,p1,p2,R,T,focal_length,principle_point,mask);
    std::cout<<R.size()<<std::endl;
//    std::cout<<"sfad"<<std::endl;

    if (((double)pass_count) / feasible_count < 0.7)
        return false;
    return true;
}
