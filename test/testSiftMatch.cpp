//
// Created by wang on 19-2-26.
//

#include "Frame.h"
#include "svf.h"

int main(){
    cv::Mat image1=cv::imread("3.jpg");
    cv::Mat image2=cv::imread("4.jpg");
    float siftRatio = 0.85;
    bool removeRepeat = true;
//    cv::resize(image1, image1, cv::Size(image1.cols/8, image1.rows/8), (0, 0), (0, 0), cv::INTER_LINEAR);
//    cv::resize(image2, image2, cv::Size(image2.cols/8, image2.rows/8), (0, 0), (0, 0), cv::INTER_LINEAR);
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


//    std::vector<cv::DMatch> matches;
//    matches=frame2->matchImage(frame1->descriptors);
    cv::Mat img_matches;


    cv::drawMatches(frame1->img,frame1->keypoints,frame2->img,frame2->keypoints,refineMatches,img_matches);
    cv::imwrite("match4.jpg",img_matches);
    cv::waitKey(0);

//    cv::drawKeypoints(frame2->img,frame2->keypoints,frame2->img);
//    cv::namedWindow("pcj",0);
//    cv::imshow("pcj",frame2->img);
//    cv::waitKey(0);
}