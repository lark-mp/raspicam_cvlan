CAM_WIDTH=640
CAM_HEIGHT=480
CAM_FRAMERATE=30

ENCODE_BITRATE=3000000

HOST_IP=192.168.10.101

./raspicam_cvlan | gst-launch-1.0 fdsrc ! videoparse format=GST_VIDEO_FORMAT_I420 width=${CAM_WIDTH} height=${CAM_HEIGHT} framerate=${CAM_FRAMERATE}/1 ! omxh264enc target-bitrate=${ENCODE_BITRATE} control-rate=variable ! video/x-h264,width=${CAM_WIDTH},height=${CAM_HEIGHT},stream-format=byte-stream,profile=high ! h264parse ! udpsink host=${HOST_IP} port=50501
