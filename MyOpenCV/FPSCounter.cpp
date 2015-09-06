#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "FPSCounter.hpp"

FPSCounter::FPSCounter() :
  m_f(0.),
  m_startTime(0),
  m_cnt(0),
  m_oldcnt(0),
  m_nowTime(0),
  m_diffTime(0),
  m_efps(0),
  m_ss()
{
  m_f = (1000 /getTickFrequency());
  m_startTime = getTickCount();
}



void FPSCounter::ProcessFrame(Mat& frame)
{
  m_cnt++;
  m_nowTime = getTickCount();  
  m_diffTime = (int)((m_nowTime- m_startTime) * m_f);
  
  if (m_diffTime >= 1000) {
    m_startTime = m_nowTime;
    m_efps = m_cnt - m_oldcnt;
    m_oldcnt = m_cnt;
    m_ss.str("");
    m_ss << m_efps << "fps";
  }

  putText(frame, m_ss.str().c_str(), Point(0,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
}
