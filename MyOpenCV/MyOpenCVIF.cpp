#include "MyOpenCVIF.hpp"

MyOpenCVIF::MyOpenCVIF() :
  m_FPSCounter(),
  m_humanDetector("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml")
{
}

void MyOpenCVIF::ProcessFrame(Mat& frame)
{
  m_FPSCounter.ProcessFrame(frame);
  //m_systemMonitor.ProcessFrame(frame);
  //m_humanDetector.ProcessFrame(frame);
  m_HUD.ProcessFrame(frame);
}
