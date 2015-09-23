#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>

#include "../robidouille/raspicam_cv/RaspiCamCV.h"
#include "MyOpenCV/MyOpenCVIterator.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
  
  RASPIVID_CONFIG* raspiConfig = (RASPIVID_CONFIG*)malloc(sizeof(RASPIVID_CONFIG));
  raspiConfig->width      = 640;
  raspiConfig->height     = 480;
  raspiConfig->bitrate    = 0;
  raspiConfig->framerate  = 0;
  raspiConfig->monochrome = 0;

  int option;
  while ((option=getopt(argc, argv, "sl")) != -1){
    switch (option){
    case 's':
      raspiConfig->width = 320;
      raspiConfig->height = 240;
      break;
    case 'l':
      raspiConfig->width = 960;
      raspiConfig->height = 720;
      break;
    default:
      fprintf(stderr, "Usage: %s [-x] [-l]\n", argv[0], option);
      fprintf(stderr, "-s: 320x240\n");
      fprintf(stderr, "-l: 960x720\n");
      exit(1);
    }
  }

  RaspiCamCvCapture * capture = (RaspiCamCvCapture *) raspiCamCvCreateCameraCapture2(0, raspiConfig); 
  free(raspiConfig);

  double fps = raspiCamCvGetCaptureProperty(capture, CV_CAP_PROP_FPS);    
  CvSize size = cvSize((int)raspiCamCvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH),
		       (int)raspiCamCvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));

  CvVideoWriter* writer = cvCreateVideoWriter("pipe:1", 
					      CV_FOURCC('I', '4', '2', '0'),
					      fps, size, 1);
  if(writer == NULL){
    printf("Create video writer failed.\n");
    return 1;
  }

  MyOpenCVIterator myOpenCVIterator;
  myOpenCVIterator.Initialize();

  do {
    Mat ReferenceFrame = cvarrToMat(raspiCamCvQueryFrame(capture));
	
    myOpenCVIterator.ProcessFrame(ReferenceFrame);

    IplImage image = ReferenceFrame;
    cvWriteFrame( writer, &image );

  } while (1);

  cvReleaseVideoWriter(&writer);
  raspiCamCvReleaseCapture(&capture);
  return 0;
}
