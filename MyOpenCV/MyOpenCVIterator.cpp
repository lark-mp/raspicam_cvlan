#include <thread>

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
  m_cvMain.push_back(new HumanDetector("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"));

  m_cvThread.push_back(new FPSCounter());
  m_cvThread.push_back(new HUD());
  m_cvThread.push_back(new SystemMonitor());
}


void MyOpenCVIterator::ThreadWorker(MyOpenCVIF* myCV, Mat& frame)
{
  myCV->ProcessFrame(frame);
}

void MyOpenCVIterator::ProcessFrame(Mat& frame)
{
  vector<std::thread> threads;
  for(auto i: m_cvThread){
    threads.push_back(std::thread(&MyOpenCVIterator::ThreadWorker,this, i, frame));
  }

  for(auto i: m_cvMain){
    i->ProcessFrame(frame);
  }

  for(std::thread &th: threads){
    th.join();
  }
}
