#ifndef __OPENCV_IF_HPP
#define __OPENCV_IF_HPP

#include <opencv2/core/core.hpp>

#include "FPSCounter.hpp"
#include "SystemMonitor.hpp"
#include "HumanDetector.hpp"
#include "HUD.hpp"

using namespace std;
using namespace cv;

class MyOpenCVIF
{
private:
  FPSCounter m_FPSCounter;
  SystemMonitor m_systemMonitor;
  HumanDetector m_humanDetector;
  HUD m_HUD;
public:
  MyOpenCVIF();
  ~MyOpenCVIF(){}

  void ProcessFrame(Mat& frame);
};

#endif
