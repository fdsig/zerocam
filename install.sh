#!/usr/bin/env bash
set -e

# Update package index
sudo apt-get update

# Install all necessary packages for building and running the C++ project
sudo apt-get update && sudo apt-get install -y \
    build-essential \
    g++-aarch64-linux-gnu \
    cmake \
    pkg-config \
    libopencv-dev \
    v4l-utils
