#include <iostream>
#include <functional>
#include <filesystem>
#include <glob.h>
#include "../src/def_utils.h"
#include "../src/LongExposure.h"
#include "../src/MotionInterpolator.h"
#include "../src/VideoOutput.h"

namespace sys = std::filesystem;

int main(int argc, char **argv) {
    std::function<void(std::string)> print = [](std::string file) {
        std::cout << file << std::endl;
    };

    std::function<std::vector<std::string>(std::string)> globVector = [](const std::string &pattern) {
        glob_t glob_result;
        glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
        std::vector<std::string> files;
        for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
            files.push_back(std::string(glob_result.gl_pathv[i]));
        }
        globfree(&glob_result);
        return files;
    };

    std::function<Frames(Frames, uchar)> motion = [](Frames frames, uchar speed) {
        Frames timeLapseFrames;
        Frames interpolatedFrames;

        for (unsigned int i = 1, j = 0; i < frames.size(); i++, j++) {
            timeLapseFrames.push_back(frames[j]);
            interpolatedFrames = MotionInterpolator::interpolatedFrames(frames[j], frames[i], speed);
            timeLapseFrames.insert(timeLapseFrames.end(), interpolatedFrames.begin(), interpolatedFrames.end());
        }

        return timeLapseFrames;
    };

    const uchar step = 6;

    // Motion Interpolation

    std::string path = "./assets/*.jpg";
    std::vector<std::string> files = globVector(path);
    Frames frames;
    for (unsigned int i = 0; i < files.size(); i + step) {
        frames.push_back(
                cv::imread(files[i])
        );
    }
    cv::imwrite("./long_exposure.jpg", LongExposure::processFrames(frames));


    VideoOutput output("./motion.mp4", 30, cv::Size(480, 640));
    output.addFrames(motion(frames, 3));
    output.save();

    // Interesting feature

    Frames feature;
    LongExposure longExposure;

    for (unsigned int i = 0; i < frames.size(); i++) {
        if (i != 0 && i % step == 0) {
            feature.push_back(longExposure.get());
            longExposure = LongExposure();
        }
        longExposure.put(frames[i]);
    }


    output = VideoOutput("./feature.mp4", 30, cv::Size(480, 640));
    output.addFrames(motion(feature, 3));
    output.save();

    return 0;
}
