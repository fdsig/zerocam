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

int main(int argc, char** argv) {
    // 1) Optionally load the V4L2 kernel module as before
    system("sudo modprobe bcm2835-v4l2");
    
    // 2) Open the camera with raw V4L2 calls
    int fd = ::open("/dev/video19", O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open /dev/video19: " 
                  << std::strerror(errno) << std::endl;
        return -1;
    }

    // 3) Set custom V4L2 controls, e.g., hevc_start_code
    //    (Replace 0x00a40a96 with the desired control ID and 1 with the desired value)
    if (!setV4L2Control(fd, 0x00a40a96, 1)) {
        std::cerr << "Warning: could not set hevc_start_code to 1.\n";
    }

    // Close raw V4L2 descriptor
    ::close(fd);

    // 4) Now proceed with OpenCV capture the way you normally do:
    cv::VideoCapture cap;
    cap.open("/dev/video19", cv::CAP_V4L2);

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera via V4L2." << std::endl;
        return -1;
    }

    // Create folder, main loop to capture frames, etc...
    std::string folder_name = "frames";
    std::string command = "mkdir -p " + folder_name;
    system(command.c_str());
    int frame_count = 0;

    while (true) {
        cv::Mat frame;
        cap >> frame;   // Acquire new frame

        if (frame.empty()) {
            std::cerr << "Warning: blank frame grabbed! Exiting..." << std::endl;
            break;
        }

        // Save the frame
        std::ostringstream filename;
        filename << folder_name << "/frame_" << frame_count++ << ".jpg";
        cv::imwrite(filename.str(), frame);

        // Exit the loop if the user presses 'q'
        if ((char)cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Cleanup
    cap.release();
    cv::destroyAllWindows();
    return 0;
}

