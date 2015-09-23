#ifndef __MYOPENCV_HUD_HPP
#define __MYOPENCV_HUD_HPP

#include "MyOpenCVIF.hpp"

using namespace std;
using namespace cv;

class HUD : public MyOpenCVIF
{
private:
public:
  HUD(){}
  ~HUD(){}

  virtual void ProcessFrame(Mat& frame);
};


#endif
