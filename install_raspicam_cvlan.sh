#!/bin/sh

# Confirm installation directory
if [ `pwd` != "/home/pi/git/raspicam_cvlan" ]; then
	echo "You have to install raspicam_cvlan at /home/pi/git/raspicam_cvlan"
	exit 1
fi

# Upgrade Raspbian to the latest environment
sudo apt-get update
sudo apt-get -y upgrade

# Install required packages
#sudo apt-get -y install build-essential cmake cmake-qt-gui pkg-config libpng12-0 libpng12-dev libpng++-dev libpng3 libpnglite-dev zlib1g-dbg zlib1g zlib1g-dev pngtools libtiff4-dev libtiff4 libtiffxx0c2 libtiff-tools
sudo apt-get -y install build-essential cmake pkg-config libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libgtk2.0-dev
#sudo apt-get -y install libjpeg8 libjpeg8-dev libjpeg8-dbg libjpeg-progs ffmpeg libavcodec-dev libavcodec53 libavformat53 libavformat-dev gstreamer1.0 gstreamer1.0-tools libxine1-ffmpeg libxine-dev libxine1-bin libunicap2 libunicap2-dev libdc1394-22-dev libdc1394-22 libdc1394-utils swig libv4l-0 libv4l-dev python-numpy libpython2.6 python-dev python2.6-dev libgtk2.0-dev pkg-config
#sudo apt-get install libswscale-dev
sudo apt-get -y install gstreamer1.0 gstreamer1.0-tools
sudo apt-get -y install pv

# Install OpenCV 3.2.0
sudo chmod 777 /usr/local/src
cd /usr/local/src
wget https://github.com/opencv/opencv/archive/3.2.0.zip
mv 3.2.0.zip opencv-3.2.0.zip
unzip opencv-3.2.0.zip
mv opencv-3.2.0 opencv-3.2.0-raspicam_cvlan

wget https://github.com/opencv/opencv_contrib/archive/3.2.0.zip
mv 3.2.0.zip opencv_contrib-3.2.0.zip
unzip opencv_contrib-3.2.0.zip
mv opencv_contrib-3.2.0 opencv-contrib-3.2.0-raspicam_cvlan

cd opencv-3.2.0-raspicam_cvlan
mkdir build
cd build
cmake -D OPENCV_EXTRA_MODULES_PATH=../../opencv-contrib-3.2.0-raspicam_cvlan/modules -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_CUDA=OFF -D WITH_CUFFT=OFF -D WITH_OPENCL=OFF -D WITH_OPENCLAMDBLAS=OFF -D WITH_OPENCLAMDFFT=OFF ..
# Modify a few lines for raspicam_cvlan
sed -i -e "1861s/NULL, filename, NULL/\"rawvideo\", filename, NULL/" ../modules/videoio/src/cap_ffmpeg_impl.hpp
sed -i -e "1863s/NULL, filename, NULL/\"rawvideo\", filename, NULL/" ../modules/videoio/src/cap_ffmpeg_impl.hpp
make -j4
sudo make install
sudo ldconfig

# Install Raspberry Pi userland
cd  ~/git
mkdir raspberrypi
cd raspberrypi
git clone https://github.com/raspberrypi/userland.git
cd userland
sudo ./buildme

# Install raspicam_cv
cd  ~/git
git clone https://github.com/robidouille/robidouille.git
cd robidouille/raspicam_cv
mkdir objs
# Modify Makefile for OpenCV3.2
sed -i -e "3s/usr\/include\/opencv/usr\/local\/include\/opencv -I\/usr\/local\/include\/opencv2\//" Makefile
sed -i -e "4s/-lopencv_legacy//" Makefile
sed -i -e "17s/BUILD/#BUILD/" Makefile
sed -i -e "18s/#//" Makefile

# Install raspicam_cvlan
cd ~/git/raspicam_cvlan
chmod 755 send_scripts/*.sh
mkdir objs
make -j4

