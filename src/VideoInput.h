#ifndef LIBCAM_VIDEOINPUT_H
#define LIBCAM_VIDEOINPUT_H

#include <opencv2/videoio.hpp>

class VideoInput {
private:
    cv::VideoCapture capture;
public:
    VideoInput(const std::string& path);

    u_long getFrameCount();

    cv::Mat getNextFrame();
};

#endif // LIBCAM_VIDEOINPUT_H
