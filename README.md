# zerocam

this repostoyr is c++ caputeur of cameras from edge dveices for computer vision applicaiotns.

the objective is to stream to private network using socket protocol which can be used by other applications on a private network.


### installation dietpi instructions

1. download dietpi os for raspberry pi 4 [here](https://dietpi.com/#downloadinfo) [image](https://dietpi.com/downloads/images/DietPi_RPi-ARMv8-Bookworm.img.xz)
2. flash dietpi os on sd card for raspberry pi 4 using [balena etcher](https://www.balena.io/etcher/)
3. take out sd card and reinsrt and edit the [dietpi.txt](dietpi.txt) to make headless (see [dietpi.txt](dietpi.txt) for more details)
4. enter wifi credentials in [dietpi-wifi.txt](dietpi-wifi.txt)
5. insert sd card into raspberry pi 4 and power on
6. ssh into raspberry pi 4 using `ssh pi@raspberrypi.local` and the password `dietpi`
7. run `sudo apt update && sudo apt upgrade -y` to update and upgrade the os
9. run `sudo apt-get install -y git cmake openssh-client libopencv-dev build-essential` to cmake git and openssh-client
10. set up ssh key for github using `ssh-keygen -t ed25519 -C "your_email@example.com"`
11. evaluate the ssh key using `cat ~/.ssh/id_ed25519.pub` and add it to github
12. start ssh agent using `eval $(ssh-agent -s)`
13. add ssh key to ssh agent using `ssh-add ~/.ssh/id_ed25519`
14. run `git clone https://github.com/zerocam/zerocam.git` to clone the repository
11. run `cd zerocam` to navigate to the repository directory
12. run `mkdir build && cd build` to create and navigate to the build directory
13. run `cmake ..` to configure the build system
14. run `make` to build the project
11. run `sudo make install` to install the project


Here we have developed in two parts using a raspberry pi 4 as a dev enviroment -- much faster for compiling and testing on the same os and then deploy to rasberry pi zero w.
