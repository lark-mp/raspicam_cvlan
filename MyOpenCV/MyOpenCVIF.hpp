#ifndef __OPENCV_IF_HPP
#define __OPENCV_IF_HPP

#include <opencv2/core/core.hpp>

class MyOpenCVIF
{
private:
public:
  MyOpenCVIF(){}
  virtual ~MyOpenCVIF(){}

  virtual void ProcessFrame(cv::Mat& frame) = 0;
};

#endif
