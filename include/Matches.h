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
    int score;
    Frame fr1,fr2;


    Match(Frame& fr1,Frame& fr2);

private:
    float siftRatio = 0.85;
    bool removeRepeat = true;
};


#endif //SIMPLESFM_MATCHER_H
