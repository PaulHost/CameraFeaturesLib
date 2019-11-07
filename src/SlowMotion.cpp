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

void interpolateFrame(cv::Mat flow,cv::Mat previous_frame, cv::Mat& frame, double interpolation_value) {
    cv::Mat result;
    flow.forEach<cv::Point2f>([&](cv::Point2f& direction, const int position[]) {
        uchar x = std::round(position[0] + (direction.x * interpolation_value));
        uchar y = std::round(position[1] + (direction.y * interpolation_value));
        frame.at<cv::Point3_<uint8_t>>(x, y) += previous_frame.at<cv::Point3_<uint8_t>>(position[0], position[1]) * interpolation_value;
    });

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

    for (uchar i = 1; i <= frame_count; i++) {
        cv::Mat frame(previous_frame.rows, previous_frame.cols, CV_8UC3,cv::Scalar(0, 0, 0));
        interpolateFrame(forward_flow, previous_frame, frame, interpolation_value * i);
        interpolateFrame(backward_flow, current_frame, frame, 1 - (interpolation_value * i));
        result[i] = frame;
    }

    return result;
}
