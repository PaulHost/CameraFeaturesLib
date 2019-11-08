#include "VideoOutput.h"

VideoOutput::VideoOutput(const std::string &path, const uchar fps, const cv::Size &size) {
    writer = cv::VideoWriter(path, cv::VideoWriter::fourcc('P', 'I', 'M', '1'), fps, size, true);
}

void VideoOutput::addFrame(const cv::Mat &frame) {
    writer.write(frame);
}

void VideoOutput::save() {
    writer.release();
}
