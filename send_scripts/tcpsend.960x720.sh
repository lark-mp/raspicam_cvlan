CAM_WIDTH=960
CAM_HEIGHT=720
CAM_FRAMERATE=30

ENCODE_BITRATE=10000000

HOST_IP=192.168.10.100

./raspicam_cvlan -l | gst-launch-1.0 fdsrc ! videoparse format=GST_VIDEO_FORMAT_I420 width=${CAM_WIDTH} height=${CAM_HEIGHT} framerate=${CAM_FRAMERATE}/1 ! omxh264enc target-bitrate=${ENCODE_BITRATE} control-rate=variable ! video/x-h264,width=${CAM_WIDTH},height=${CAM_HEIGHT},stream-format=byte-stream,profile=high ! h264parse ! tcpclientsink host=${HOST_IP} port=5001 sync=false
