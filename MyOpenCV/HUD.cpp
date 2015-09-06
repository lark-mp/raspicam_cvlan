#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "HUD.hpp"

void HUD::ProcessFrame(Mat& frame)
{
  line(frame, Point(180, 100), Point(180, 380), Scalar(0,200,0), 2, CV_AA);
  line(frame, Point(460, 100), Point(460, 380), Scalar(0,200,0), 2, CV_AA);
  rectangle(frame, Point(40, 360), Point(120, 440), Scalar(0,255,0), 2, 4);
  circle(frame, Point(80, 400), 10, Scalar(0,200,0), 1, CV_AA);
  circle(frame, Point(80, 400), 30, Scalar(0,200,0), 1, CV_AA);
  
  putText(frame, "SPEED", Point(110,240), FONT_HERSHEY_PLAIN, 1.2, Scalar(0,200), 1, CV_AA);
  putText(frame, "XXXkm", Point(110,260), FONT_HERSHEY_PLAIN, 1.2, Scalar(0,200), 1, CV_AA);
  
  putText(frame, "ALT", Point(470,240), FONT_HERSHEY_PLAIN, 1.2, Scalar(0,200), 1, CV_AA);
  putText(frame, "XXXXm", Point(470,260), FONT_HERSHEY_PLAIN, 1.2, Scalar(0,200), 1, CV_AA);
}
