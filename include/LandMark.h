//
// Created by wang on 19-2-26.
//

#ifndef SIMPLESFM_LANDMARK_H
#define SIMPLESFM_LANDMARK_H

class Landmark{
    cv::Point3f pt;
    int seen = 0; // how many camera have seen this point
};

#endif //SIMPLESFM_LANDMARK_H
