# raspicam_cvlan
raspicam_cvlan is an easy-to-use installer and program that enables raspberry pi 2 to show camera module streaming video with OpenCV over LAN.

The script is for Raspbian. Tested version is 2015-05-05.
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
### 1. If you want to show streaming video locally in RasPi2
#### Start raspicam_cvlan

Run ``tcpsend.sh`` on your shell.

A warning shown below occurs, but this is normal.

```bash
OpenCV: FFMPEG: tag 0x30323449/'I420' is not supported with codec id 14 and format 'rawvideo / raw video'
```

RasPi2 is now waiting for an access from a client.

#### Show video with mplayer

Run following script in another shell.

```cmd
mplayer -demuxer h264es -vo direct3d -fps 60 ffmpeg://tcp://127.0.0.1:5001
```

### 2. If you want to show streaming video over LAN

#### On Raspberry Pi2

##### Start raspicam_cvlan

Run ``tcpsend.sh`` on your shell.

A warning shown below occurs, but this is normal.

```bash
OpenCV: FFMPEG: tag 0x30323449/'I420' is not supported with codec id 14 and format 'rawvideo / raw video'
```

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
## Credits
The project is inspired by [raspicam_cv](https://github.com/robidouille/robidouille/tree/master/raspicam_cv "raspicam_cv").

Referred [here](http://blog.studiok-i.net/raspberry-pi/1244.html) and [here](http://blog.studiok-i.net/raspberry-pi/848.html) to create the installer.

Referred [here](http://iwaki2009.blogspot.jp/2012/08/opencvfps.html) to implement FPS counter class.

Referred [here](http://myenigma.hatenablog.com/entry/2015/04/27/185822) to implement system monitor class.

Special thanks to [sa](https://twitter.com/sa_tsuklog "sa_tsuklog") and [colmuska](https://twitter.com/colmuska "colmuska").
