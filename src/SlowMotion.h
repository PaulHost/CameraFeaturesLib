#ifndef SLOWMOTION_H
#define SLOWMOTION_H

#include <iostream>
#include <algorithm>
#include <functional>

#include <opencv2/opencv.hpp>

class SlowMotion
{
private:

public:
    std::vector<cv::Mat> interpolatedFrame(cv::Mat previous_frame, cv::Mat next_frame, int frame_count);
};

#endif // SLOWMOTION_H
