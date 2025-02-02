#!/usr/bin/env bash
set -e

# Update package index
sudo apt-get update

# Install all necessary packages for building and running the C++ project
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    libopencv-dev \

