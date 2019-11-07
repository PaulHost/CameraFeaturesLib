#include "SlowMotion.h"

cv::Mat toGrayScale(cv::Mat frame) {
    cv::Mat gray_frame;
    cv::cvtColor(frame,gray_frame, cv::COLOR_BGR2GRAY);
    return gray_frame;
}

cv::Mat calculateOpticalFlow(cv::Mat first, cv::Mat second) {
    cv::Mat result;
    cv::calcOpticalFlowFarneback(first, second, result, 0.5, 3, 15, 3, 3, 1.2, 0);
    return result;
}

cv::Mat interpolatedFrame(cv::Mat  cv::Mat interpolation_direction, double interpoltion_value) {
    cv::Mat result;

}

std::vector<cv::Mat> SlowMotion::interpolatedFrames(cv::Mat previous_frame, cv::Mat current_frame, uchar frame_count) {
    cv::Mat previous_frame_gray = toGrayScale(previous_frame);
    cv::Mat current_frame_gray = toGrayScale(current_frame);

    cv::Mat forward_flow = calculateOpticalFlow(previous_frame, current_frame);
    cv::Mat backward_flow = calculateOpticalFlow(current_frame, previous_frame);

    cv::Mat forward_flow_step = forward_flow / frame_count;
    cv::Mat backward_flow_step = backward_flow / frame_count;

    std::vector<cv::Mat> result(frame_count);
    double interpolation_value = 1 / frame_count;

    for (uchar i = 0; i <= frame_count; i++) {



    }

    return result;
}
