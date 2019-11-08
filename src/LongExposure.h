#ifndef LONGEXPOSURE_H
#define LONGEXPOSURE_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <opencv2/opencv.hpp>

typedef std::vector<cv::Mat> Frames;

class LongExposure {
private:
    u_long count;

    cv::Mat everaged_frame;
public:
    LongExposure(cv::Mat);

    LongExposure(const Frames);

    LongExposure *put(cv::Mat);

    cv::Mat get();

    static cv::Mat processFrames(Frames);
};

#endif // LONGEXPOSURE_H
