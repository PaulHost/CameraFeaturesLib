#ifndef LIBCAM_MOTIONINTERPOLATOR_H
#define LIBCAM_MOTIONINTERPOLATOR_H

#include "def_utils.h"
#include <iostream>

#include <algorithm>
#include <opencv2/opencv.hpp>

class MotionInterpolator {
public:
    Frames interpolatedFrames(cv::Mat previous_frame, cv::Mat current_frame, uchar frame_count);
};

#endif // LIBCAM_MOTIONINTERPOLATOR_H
