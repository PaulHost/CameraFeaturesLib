#ifndef LIBCAM_MOTIONINTERPOLATOR_H
#define LIBCAM_MOTIONINTERPOLATOR_H

#include "def_utils.h"
#include <iostream>

#include <algorithm>
#include <opencv2/opencv.hpp>

class MotionInterpolator {
public:
    static Frames interpolatedFrames(const cv::Mat &previous_frame, const cv::Mat &current_frame, uchar frame_count);

    static Frames interpolate(const cv::Mat &previous_frame, const cv::Mat &current_frame, uchar frame_count);
};

#endif // LIBCAM_MOTIONINTERPOLATOR_H
