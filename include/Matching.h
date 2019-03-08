//
// Created by wang on 19-2-26.
//

#ifndef SIMPLESFM_MATCHER_H
#define SIMPLESFM_MATCHER_H

#include "Frame.h"
#include "svf.h"

class Frame;

class Match{
public:
    int fr1,fr2;

    cv::Mat R;
    cv::Mat T;
    vector<DMatch> matches;

    Match(int fr1, int fr2);

private:
    int score;
    float siftRatio = 0.85;
    bool removeRepeat = true;
};


#endif //SIMPLESFM_MATCHER_H
