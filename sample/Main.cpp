#include <iostream>
#include <functional>
#include <filesystem>
#include <glob.h>
#include <string>
#include "../src/def_utils.h"
#include "../src/LongExposure.h"
#include "../src/MotionInterpolator.h"
#include "../src/VideoOutput.h"

namespace sys = std::filesystem;

void print (std::string file) {
    std::cout << file << std::endl;
};

std::vector<std::string> globVector (const std::string &pattern) {
    glob_t glob_result;
    glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
    std::vector<std::string> files;
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
        files.push_back(std::string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
};

Frames motion (Frames frames, uchar speed) {
    Frames timeLapseFrames;
    timeLapseFrames.push_back(frames[0]);

    for (unsigned int i = 1; i < frames.size(); i++) {
			std::cout << "Processing frame " << i << std::endl; 
    	Frames interpolatedFrames = MotionInterpolator::interpolatedFrames(frames[i - 1], frames[i], speed);
			for (auto& frame : interpolatedFrames) {
				timeLapseFrames.push_back(frame);
			}
    	timeLapseFrames.push_back(frames[i]);
    }

    return timeLapseFrames;
};

Frames blur_all(Frames frames){
	Frames res_frames;
	for(auto& frame: frames){
		cv::Mat tmp;
		cv::medianBlur(frame, tmp, 3);
		res_frames.push_back(tmp);
	}
	return res_frames;
}

int main(int argc, char **argv) {

//    const uchar step = 6;
		const uchar speed = 3;

    // Long Exposure Pictures

    std::string path = "./assets/*.jpg";
    std::vector<std::string> files = globVector(path);
    Frames frames;

	  for (auto& file : files) {
			cv::Mat resized = cv::imread(file);
			cv::resize(resized, resized, cv::Size(0,0), 0.125, 0.125);
			frames.push_back(resized);
		}

//    cv::imwrite("./long_exposure.jpg", LongExposure::processFrames(frames));
//
		VideoOutput output("./motion.avi", 30, cv::Size(frames[0].cols, frames[0].rows));
		output.addFrames(blur_all(motion(frames, speed))); 
		output.save();
//
//		for (auto& f: frames) { std::cout << f.rows << " x " << f.cols << std::endl; }
//
    VideoOutput output_orig("./motion_orig.avi", 30 * (speed + 1), cv::Size(frames[0].cols, frames[0].rows));
    output_orig.addFrames(frames);
    output_orig.save();

    // Interesting feature

//    Frames feature;
//    LongExposure longExposure;
//
//    for (unsigned int i = 0; i <10; i++) {
//        if (i != 0 && i % step == 0) {
//            feature.push_back(longExposure.get());
//            longExposure = LongExposure();
//        }
//        longExposure.put(frames[i]);
//    }
//
//
//    output = VideoOutput("./feature.mp4", 30, cv::Size(frames[0].cols, frames[0].rows));
//    output.addFrames(motion(feature, 3));
//    output.save();

    return 0;
}
