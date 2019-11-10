#include <iostream>
#include <functional>
#include <filesystem>
#include <glob.h>
#include "../src/def_utils.h"
#include "../src/LongExposure.h"

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
            files.emplace_back(glob_result.gl_pathv[i]);
        }
        globfree(&glob_result);
        return files;
    };


    std::string path = "./assets/*.jpg";
    std::vector<std::string> files = globVector(path);
    Frames frames;
    for (int i = 0; i < files.size(); i++) {
        frames.push_back(
                cv::imread(files[i])
        );
    }
    cv::imwrite("./long_exposure.jpg", LongExposure::processFrames(frames));

    return 0;
}
