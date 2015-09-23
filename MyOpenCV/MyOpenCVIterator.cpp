#include <pthread.h>

#include "MyOpenCVIterator.hpp"

#include "FPSCounter.hpp"
#include "SystemMonitor.hpp"
#include "HumanDetector.hpp"
#include "HUD.hpp"

MyOpenCVIterator::MyOpenCVIterator()
{
}

void MyOpenCVIterator::Initialize()
{
  m_myOpenCVVec.push_back(new FPSCounter());
  m_myOpenCVVec.push_back(new SystemMonitor());
  m_myOpenCVVec.push_back(new HUD());
  m_myOpenCVVec.push_back(new HumanDetector("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"));
}

void MyOpenCVIterator::ProcessFrame(Mat& frame)
{
  for(auto i: m_myOpenCVVec){
    i->ProcessFrame(frame);
  }
}
