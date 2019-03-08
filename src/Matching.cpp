//
// Created by wang on 19-2-26.
//
#include "Matching.h"

Match::Match(Frame &fr1, Frame &fr2) {
    fr1.ExtractSIFT();
    fr2.ExtractSIFT();

    std::vector<std::vector<cv::DMatch>> matches;
    std::vector<cv::DMatch> goodMatches;
    cv::FlannBasedMatcher siftMatcher;
    siftMatcher.knnMatch(fr1.descriptors,fr2.descriptors,matches,2);
    for (int i = 0; i < matches.size(); ++i) {
        if (matches[i][0].distance<siftRatio*matches[i][1].distance){
            goodMatches.push_back(matches[i][0]);
        }
    }
    std::vector<cv::DMatch> refineMatches = getInliers(fr1.keypoints, fr2.keypoints, goodMatches, removeRepeat);


}
