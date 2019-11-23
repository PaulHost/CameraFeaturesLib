#include "VideoOutput.h"

VideoOutput::VideoOutput(const std::string &path, const uchar fps, const cv::Size &size) {
    writer = cv::VideoWriter(path, cv::VideoWriter::fourcc('X','2','6','4'), fps, size, true);
}

void VideoOutput::addFrame(const cv::Mat &frame) {
    writer.write(frame);
}

void VideoOutput::addFrames(const Frames &frames) {
	for (const cv::Mat& f : frames)  writer.write(f);
}

void VideoOutput::save() {
    writer.release();
}
