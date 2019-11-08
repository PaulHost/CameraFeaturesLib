#ifndef SLOWMOTION_H
#define SLOWMOTION_H

#include <iostream>
#include <algorithm>

#include <opencv2/opencv.hpp>

class SlowMotion {
public:
    std::vector<cv::Mat> interpolatedFrames(cv::Mat previous_frame, cv::Mat current_frame, uchar frame_count);
};

#endif // SLOWMOTION_H
