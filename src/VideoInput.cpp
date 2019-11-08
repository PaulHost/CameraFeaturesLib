#include "VideoInput.h"

VideoInput::VideoInput(const std::string& path) {
    capture.open(path);
}

u_long VideoInput::getFrameCount() {
    return capture.get(cv::CAP_PROP_FRAME_COUNT);
}

cv::Mat VideoInput::getNextFrame() {
    cv::Mat frame;
    capture >> frame;
    return frame;
}
