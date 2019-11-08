#include "LongExposure.h"

LongExposure::LongExposure(const cv::Mat frame) {
    count = 1;
    everaged_frame = frame;
}

LongExposure::LongExposure(const Frames frames) {
    count = frames.size();
    everaged_frame = processFrames(frames);
}

LongExposure *LongExposure::put(const cv::Mat frame) {
    u_long new_count = count + 1;
    everaged_frame = (everaged_frame * count / new_count) + (frame / new_count);
    count = new_count;
    return this;
}

cv::Mat LongExposure::get() {
    return everaged_frame;
}

cv::Mat LongExposure::processFrames(const Frames frames) {
    return std::accumulate(frames.begin() + 1, frames.end(), frames[0]) / frames.size();
}
