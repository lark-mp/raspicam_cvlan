#!/bin/sh

if [ `pwd` != "/home/pi/git/raspicam_cvlan" ]; then
	echo "You have to install raspicam_cvlan at /home/pi/git/raspicam_cvlan"
	exit 1
fi

sudo apt-get update
sudo apt-get -y upgrade

sudo apt-get -y install build-essential cmake cmake-qt-gui pkg-config libpng12-0 libpng12-dev libpng++-dev libpng3 libpnglite-dev zlib1g-dbg zlib1g zlib1g-dev pngtools libtiff4-dev libtiff4 libtiffxx0c2 libtiff-tools
sudo apt-get -y install libjpeg8 libjpeg8-dev libjpeg8-dbg libjpeg-progs ffmpeg libavcodec-dev libavcodec53 libavformat53 libavformat-dev gstreamer1.0 gstreamer1.0-tools libxine1-ffmpeg libxine-dev libxine1-bin libunicap2 libunicap2-dev libdc1394-22-dev libdc1394-22 libdc1394-utils swig libv4l-0 libv4l-dev python-numpy libpython2.6 python-dev python2.6-dev libgtk2.0-dev pkg-config
sudo apt-get install libswscale-dev

cd
wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/3.0.0/opencv-3.0.0.zip
unzip opencv-3.0.0.zip
cd opencv-3.0.0
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_CUDA=OFF -D WITH_CUFFT=OFF -D WITH_OPENCL=OFF -D WITH_OPENCLAMDBLAS=OFF -D WITH_OPENCLAMDFFT=OFF ..
sed -i -e "1594s/NULL, filename, NULL/\"rawvideo\", filename, NULL/" ../modules/videoio/src/cap_ffmpeg_impl.hpp
sed -i -e "1596s/NULL, filename, NULL/\"rawvideo\", filename, NULL/" ../modules/videoio/src/cap_ffmpeg_impl.hpp

make -j4
sudo make install
sudo ldconfig

cd  ~/git
mkdir raspberrypi
cd raspberrypi
git clone https://github.com/raspberrypi/userland.git
cd userland
sudo ./buildme

cd  ~/git
git clone https://github.com/robidouille/robidouille.git
cd robidouille/raspicam_cv
mkdir objs
sed -i -e "3s/usr\/include\/opencv/usr\/local\/include\/opencv -I\/usr\/local\/include\/opencv2\//" Makefile
sed -i -e "4s/-lopencv_legacy//" Makefile

#cd ~/git
#git clone https://github.com/lark-mp/raspicam_cvlan.git
#cd raspicam_cvlan
cd ~/git/raspicam_cvlan
chmod 755 send_scripts/*.sh
mkdir objs
make -j4

echo "\033[34;42m raspicam_cvlan setup finished. Enjoy! ;) \033[00m"
