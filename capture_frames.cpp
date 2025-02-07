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
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cerrno>
#include <cstring>
#include <string>

static bool setV4L2Control(int fd, __u32 id, int value) {
    v4l2_control control;
    std::memset(&control, 0, sizeof(control));
    control.id = id;
    control.value = value;

    if (ioctl(fd, VIDIOC_S_CTRL, &control) < 0) {
        std::cerr << "Failed to set control with id=0x" 
                  << std::hex << id << " to value=" << std::dec << value
                  << " : " << std::strerror(errno) << std::endl;
        return false;
    }
    return true;
}

int main() {
    // Open the camera device (try /dev/video0 first)
    cv::VideoCapture cap("/dev/video0", cv::CAP_V4L2);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open /dev/video0." << std::endl;
        return -1;
    }

    // Optionally set camera properties (width/height, etc.)
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // Attempt to capture a single frame
    cv::Mat frame;
    cap.read(frame);

    if (frame.empty()) {
        std::cerr << "Warning: blank frame grabbed! Exiting..." << std::endl;
        return -1;
    }

    // Write that single frame to disk as a JPEG
    std::string filename = "capture.jpg";
    if (!cv::imwrite(filename, frame)) {
        std::cerr << "Error: Could not write image to " << filename << std::endl;
        return -1;
    }

    std::cout << "Saved " << filename << " successfully." << std::endl;

    cap.release();
    return 0;
}

