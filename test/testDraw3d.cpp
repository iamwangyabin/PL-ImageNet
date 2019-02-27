//
// Created by wang on 19-2-27.
//

#include <opencv2/opencv.hpp>
#include <opencv2/viz.hpp>

#include "Frame.h"
#include "svf.h"
#include "System.h"
using namespace cv;
using namespace std;


int main(){
    cv::Mat image1=cv::imread("3.jpg");
    cv::Mat image2=cv::imread("4.jpg");
    cv::resize(image1, image1, cv::Size(image1.cols/4, image1.rows/4), (0, 0), (0, 0), cv::INTER_LINEAR);
    cv::resize(image2, image2, cv::Size(image2.cols/4, image2.rows/4), (0, 0), (0, 0), cv::INTER_LINEAR);
    float siftRatio = 0.85;
    bool removeRepeat = true;

    Frame *frame1=new Frame(image1, 1);
    Frame *frame2=new Frame(image2, 2);
    frame1->ExtractSIFT();
    frame2->ExtractSIFT();

    std::vector<std::vector<cv::DMatch>> matches;
    std::vector<cv::DMatch> goodMatches;
    cv::FlannBasedMatcher siftMatcher;
    siftMatcher.knnMatch(frame1->descriptors,frame2->descriptors,matches,2);
    for (int i = 0; i < matches.size(); ++i) {
        if (matches[i][0].distance<siftRatio*matches[i][1].distance){
            goodMatches.push_back(matches[i][0]);
        }
    }
    std::vector<cv::DMatch> refineMatches = getInliers(frame1->keypoints, frame2->keypoints, goodMatches, removeRepeat);
    cout<<"1"<<endl;

    Mat K = Mat::eye(3, 3, CV_64F);

    K.at<double>(0,0) = 1000;
    K.at<double>(1,1) = 1000;
    K.at<double>(0,2) = frame1->img.size().width/2;
    K.at<double>(1,2) = frame1->img.size().height/2;


    std::vector<Point2f> p_frame1_kp;
    std::vector<Point2f> p_frame2_kp;
//    vector<KeyPoint> frame1_kp;
//    vector<KeyPoint> frame2_kp;
    for (int j = 0; j < refineMatches.size(); ++j) {
//        cout<<"1"<<endl;
        p_frame1_kp.push_back(frame1->keypoints[refineMatches[j].queryIdx].pt);
        p_frame2_kp.push_back(frame2->keypoints[refineMatches[j].trainIdx].pt);

    }
//    cout<<"2"<<endl;
    cout<<p_frame1_kp.size()<<endl;
    cout<<p_frame2_kp.size()<<endl;
//    void reconstruct(
//            cv::Mat& K,
//            cv::Mat& R,
//            cv::Mat& T,
//            std::vector<cv::Point2f>& p1,
//            std::vector<cv::Point2f>& p2,
//            std::vector< cv::Point3d >& points
//    )
    std::vector< cv::Point3d > points;
    frame2->find_transform(K,p_frame1_kp,p_frame2_kp);
    cout<<"3"<<endl;
    cout<<frame2->R.size()<<endl;

    reconstruct(K,frame2->R,frame2->T,p_frame1_kp,p_frame2_kp,points);

    cout<<"4"<<endl;


    for (int k = 0; k < points.size(); ++k) {
        cout<<points[k]<<endl;
    }
    viz::Viz3d myWindow("Frame");
    myWindow.showWidget("Widget",viz::WCoordinateSystem());
    viz::WCloud cloud(points,viz::Color::red());
    myWindow.showWidget("cloud 1",cloud);
    myWindow.spin();
}
