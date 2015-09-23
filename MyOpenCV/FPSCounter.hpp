#ifndef __FPS_COUNTER_HPP
#define __FPS_COUNTER_HPP

#include <opencv2/core/core.hpp>
#include "MyOpenCVIF.hpp"

using namespace std;
using namespace cv;

class FPSCounter : public MyOpenCVIF
{
 private:
  double m_f;
  int64 m_startTime;
  int m_cnt;
  int m_oldcnt;
  int64 m_nowTime;
  int64 m_diffTime;
  int m_efps;
  stringstream m_ss;
 public:
  FPSCounter();
  ~FPSCounter(){}

  virtual void ProcessFrame(Mat& frame);
};

#endif
