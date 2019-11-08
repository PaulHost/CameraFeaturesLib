#ifndef LIBCAM_LONGEXPOSURE_H
#define LIBCAM_LONGEXPOSURE_H

#include "def_utils.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <opencv2/opencv.hpp>

class LongExposure {
private:
    u_long count;

    cv::Mat averaged_frame;
public:
    LongExposure(cv::Mat);

    LongExposure(Frames);

    LongExposure *put(cv::Mat);

    cv::Mat get();

    static cv::Mat processFrames(Frames);
};

#endif // LIBCAM_LONGEXPOSURE_H
