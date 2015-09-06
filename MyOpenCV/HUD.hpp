#ifndef __MYOPENCV_HUD_HPP
#define __MYOPENCV_HUD_HPP

using namespace std;
using namespace cv;

class HUD
{
private:
public:
  HUD(){}
  ~HUD(){}

  void ProcessFrame(Mat& frame);
};


#endif
