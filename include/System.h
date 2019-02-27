//
// Created by wang on 19-2-27.
//

#ifndef SIMPLESFM_SYSTEM_H
#define SIMPLESFM_SYSTEM_H

void reconstruct(
        cv::Mat& K,
        cv::Mat& R,
        cv::Mat& T,
        std::vector<cv::Point2f>& p1,
        std::vector<cv::Point2f>& p2,
        std::vector< cv::Point3d >& points
);

#endif //SIMPLESFM_SYSTEM_H
