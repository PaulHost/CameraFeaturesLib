#ifndef LIBCAM_VIDEOOUTPUT_H
#define LIBCAM_VIDEOOUTPUT_H

#include <opencv2/videoio.hpp>
#include "def_utils.h"

class VideoOutput {
private:
    cv::VideoWriter writer;
public:
    VideoOutput(const std::string &path, uchar fps, const cv::Size &size);

    void addFrame(const cv::Mat &);

    void addFrames(const Frames &);

    void save();
};

#endif // LIBCAM_VIDEOOUTPUT_H
