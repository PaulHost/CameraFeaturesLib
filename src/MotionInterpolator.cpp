#include "MotionInterpolator.h"

cv::Mat copy(const cv::Mat& orgImage) {
    cv::Mat image;
    orgImage.copyTo(image);
    return image;
}

cv::Mat blotter(const cv::Mat& orgImage) {
    cv::Mat image;
    cv::medianBlur(orgImage, image, 5);
    return image;
}

cv::Mat blotter(const cv::Mat& first, const cv::Mat& second) {
    return (blotter(first) + blotter(second)) / 2;
}

cv::Mat getGrayScale(const cv::Mat &frame) {
    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
    return gray_frame;
}

cv::Mat calculateOpticalFlow(const cv::Mat &first, const cv::Mat& second) {
    cv::Mat result;
    cv::calcOpticalFlowFarneback(first, second, result, 0.5, 3, 15, 3, 3, 1.2, 0);
    return result;
}

void interpolateFrame(cv::Mat flow, const cv::Mat& previous_frame, cv::Mat &frame, double interpolation_value) {
  flow.forEach<cv::Point2f>([&](cv::Point2f &direction, const int position[]) {
    ulong x = std::clamp(static_cast<int>(std::round(position[0] + (direction.x * interpolation_value))), 0, flow.rows - 1);
    ulong y = std::clamp(static_cast<int>(std::round(position[1] + (direction.y * interpolation_value))), 0, flow.cols - 1);
    frame.at<cv::Point3_<uint8_t >>(x, y) += previous_frame.at<cv::Point3_<uint8_t >>(position[0], position[1]) * interpolation_value;
  });
}

Frames MotionInterpolator::interpolatedFrames(const cv::Mat& previous_frame, const cv::Mat& current_frame, uchar frame_count) {
    cv::Mat previous_frame_gray = getGrayScale(previous_frame);
    cv::Mat current_frame_gray = getGrayScale(current_frame);

    cv::Mat forward_flow = calculateOpticalFlow(previous_frame_gray, current_frame_gray);
    cv::Mat backward_flow = calculateOpticalFlow(current_frame_gray, previous_frame_gray);

    cv::Mat forward_flow_step = forward_flow / frame_count;
    cv::Mat backward_flow_step = backward_flow / frame_count;

    Frames result;
    double interpolation_value = 1 / frame_count;

    auto substrate =  blotter(previous_frame, current_frame);

    for (uchar i = 1; i <= frame_count; i++) {
        cv::Mat frame = copy(substrate);

        interpolateFrame(forward_flow_step, previous_frame, frame, interpolation_value * i);
        interpolateFrame(backward_flow_step, current_frame, frame, 1.0 - (interpolation_value * i));

        result.push_back(frame);
    }


    return result;
}

Frames MotionInterpolator::interpolate(const cv::Mat &previous_frame, const cv::Mat &current_frame, uchar frame_count) {
    cv::Mat flow = calculateOpticalFlow(getGrayScale(previous_frame), getGrayScale(current_frame));
    cv::Mat flow_step = flow / frame_count;

    Frames result;

    double interpolation_value = 1 / frame_count;
    auto substrate = blotter(current_frame);

    for (uchar i = 1; i <= frame_count; i++) {
        cv::Mat frame = copy(substrate);
        interpolateFrame(flow_step, previous_frame, frame, interpolation_value * i);
        result.push_back(frame);
    }

    return result;
}
