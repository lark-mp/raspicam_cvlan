# raspicam_cvlan
raspicam_cvlan is an easy-to-use installer and program that enables raspberry pi 2 to show camera module streaming video with OpenCV over LAN.

The script is for Raspbian. Tested version is 2015-05-05 w/OpenCV 3.0.0 and 2016-11-25 w/OpenCV 3.2.0.
## Requirements
* Raspberry Pi2
* Raspberry Pi Video Module
* Stable power supply
* Internet connection
* Windows PC/Tablet is needed when you want to watch RasPi video over LAN

## Installation
```bash
cd /home/pi
mkdir git
cd git
git clone https://github.com/lark-mp/raspicam_cvlan
cd raspicam_cvlan
sh install_raspicam_cvlan.sh
```
The installation may take an hour or more.

## Quickstart
### 1. Show video locally on LXDE (X window)
#### Start raspicam_cvlan

Run ``tcpsend.sh`` on your shell.

RasPi2 is now waiting for an access from a client.

#### Show video with gstreamer

Run the following script on another shell.

```cmd
gst-launch-1.0 tcpclientsrc host=127.0.0.1 port=5001 ! h264parse ! omxh264dec ! "video/x-raw, format=(string)I420" ! autovideosink
```

### 2. Show video over LAN

#### On Raspberry Pi2

##### Start raspicam_cvlan

Run ``tcpsend.sh`` on your shell.

RasPi2 is now waiting for an access from a client.

#### On Windows

##### Install mplayer
Download [mplayer](https://www.mplayerhq.hu/design7/dload.html) and extract the file.

##### Show sample video stream
<!-- #### Windows -->
Create a file named ``raspicam.bat`` in the extracted folder and write the following script:

```cmd
mplayer -demuxer h264es -vo direct3d -fps 60 ffmpeg://tcp://[your_raspi_IP_address]:5001
```

Make sure ``tcpsend.sh`` is running on RasPi2 and doubleclick ``raspicam.bat`` to show raspicam_cvlan video.

<!-- #### Linux
* Install mplayer with a package manager or download from [mplayer website](https://www.mplayerhq.hu/design7/dload.html).
* Type the following script on your shell:

```bash
mplayer -demuxer h264es -vo direct3d -fps 60 ffmpeg://tcp://[your_raspi_IP_address]:5001
```
-->

### Disable OpenCV samples
If you comment out lines in MyOpenCVProcessor::Initialize() in MyOpenCV/MyOpenCVProcessor.cpp, you can disable respective functions.

## How to implement your own OpenCV code
To implement your own OpenCV code, please follow the instructions below.

### Create your own MyOpenCV class
You have to inherit MyOpenCVIF and implement YourClass::ProcessFrame.
Each frame of video stream will be given as an argument "cv::Mat& frame".

### Modify Makefile
Add your object of the class to MYOBJS.

### Modify MyOpenCV/MyOpenCVProcessor.cpp
Include your header file to MyOpenCVProcessor.cpp and add an instance of your class to MyOpenCVProcessor::Initialize.
* When you add your instance to m_cvMain, the instance will process video frames in the main thread.
* When you add your instance to m_cvThread, a new thread will be automatically created and the instance will process video frames in the new thread.

## Credits
The project is inspired by [raspicam_cv](https://github.com/robidouille/robidouille/tree/master/raspicam_cv "raspicam_cv").

Referred [here](http://blog.studiok-i.net/raspberry-pi/1244.html) and [here](http://blog.studiok-i.net/raspberry-pi/848.html) to create the installer.

Referred [here](http://iwaki2009.blogspot.jp/2012/08/opencvfps.html) to implement FPS counter class.

Referred [here](http://myenigma.hatenablog.com/entry/2015/04/27/185822) to implement system monitor class.

Special thanks to [sa](https://twitter.com/sa_tsuklog "sa_tsuklog") and [colmuska](https://twitter.com/colmuska "colmuska").
