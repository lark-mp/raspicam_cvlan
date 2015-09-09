# raspicam_cvlan
raspicam_cvlan is an easy-to-use installer and program that enables raspberry pi 2 to show camera module streaming video with OpenCV over LAN.

The script is for Raspbian. Tested version is 2015-05-05.
## Quickstart
### Install packages and libraries
```bash
cd /home/pi
git clone https://github.com/lark-mp/raspicam_cvlan
cd raspicam_cvlan
sh install_raspicam_cvlan.sh
```
The installation may take an hour or more.

To show sample video to a client, start ``tcpsend.640x480.sh``.
### Show sample video stream (on Windows client)
<!-- #### Windows -->
* Download [mplayer](https://www.mplayerhq.hu/design7/dload.html) and extract 7z file.
* Create a file named ``raspicam.bat`` in the extracted folder and write the following script:

```cmd
mplayer -demuxer h264es -vo direct3d -fps 60 ffmpeg://tcp://[your_raspi_IP_address]:5001
```

* Doubleclick ``raspicam.bat`` to show raspicam_cvlan video.

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
