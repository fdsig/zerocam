// capture_frames.cpp
//
// This caputers frams from the raspberry pi camera on raspberry pi zero 2 w
// and saves them to a file.
//
// The frames are saved in a loop, and the loop is exited when the user presses
// the 'q' key.
//
// save in a folder called 'frames' 
//
// The frames are saved in a loop, and the loop is exited when the user presses
// the 'q' key.

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <sstream>
#include <iostream>

int main(int argc, char** argv) {
    // Attempt to load the V4L2 kernel module (optional, you can do this in a script)
    system("sudo modprobe bcm2835-v4l2");

    // Create VideoCapture object
    cv::VideoCapture cap;
    cap.open("/dev/video0", cv::CAP_V4L2);

    // Optionally set camera resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera via V4L2." << std::endl;
        std::cerr << "Check that bcm2835-v4l2 is loaded and /dev/video0 exists." << std::endl;
        return -1;
    }

    // Create a folder to save the frames
    std::string folder_name = "frames";
    std::string command = "mkdir -p " + folder_name;
    system(command.c_str());
    int frame_count = 0;
    
    while (true) {
        cv::Mat frame;
        cap >> frame;   // Capture a new frame

        if (frame.empty()) {
            std::cerr << "Warning: blank frame grabbed! Exiting..." << std::endl;
            break;
        }
        // Save the frame to the folder
        std::ostringstream filename;
        filename << folder_name << "/frame_" << frame_count++ << ".jpg";
        cv::imwrite(filename.str(), frame);

        // Exit the loop if the user presses 'q'
        char c = (char)cv::waitKey(1);
        if (c == 'q') {
            break;
        }
    }

    // Cleanup
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

