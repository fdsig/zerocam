#!/bin/bash

###############################################################################
# Simple Bash script to install and test Raspberry Pi camera (libcamera only).
# No Python dependencies are required.
#
# Usage:
#   1. Make it executable: chmod +x install_camera_no_python.sh
#   2. Run it as root: sudo ./install_camera_no_python.sh
###############################################################################

# Ensure we run with root privileges
if [ "$(id -u)" -ne 0 ]; then
    echo "Please run this script as root (e.g., sudo ./install_camera_no_python.sh)."
    exit 1
fi

echo "----------------------------------------"
echo "Updating and upgrading system packages..."
echo "----------------------------------------"
apt-get update && apt-get upgrade -y

echo "----------------------------------------"
echo "Installing camera-related packages (libcamera)..."
echo "----------------------------------------"
apt-get install -y libcamera-apps

# Optionally, install v4l-utils for troubleshooting:
# apt-get install -y v4l-utils

echo "----------------------------------------"
echo "Enabling camera interface via raspi-config..."
echo "----------------------------------------"

# A short pause to ensure everything is settled
sleep 2

echo "----------------------------------------"
echo "Testing camera: capturing an image with libcamera-still..."
echo "----------------------------------------"
libcamera-still -n -o /root/zerocam/test_capture.jpg

if [ -f /root/zerocam/test_capture.jpg ]; then
    echo "Camera test successful! Image saved to /root/zerocam/test_capture.jpg"
else
    echo "Camera test may have failed. Please check the error messages above."
fi

echo "----------------------------------------"
echo "Script complete!"
echo "----------------------------------------"
