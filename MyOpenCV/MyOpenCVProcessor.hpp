#ifndef __OPENCV_PROCESSOR_HPP
#define __OPENCV_PROCESSOR_HPP

#include <opencv2/core/core.hpp>
#include "MyOpenCVIF.hpp"

using namespace std;
using namespace cv;

class MyOpenCVProcessor
{
private:
  vector<MyOpenCVIF*> m_cvMain;
  vector<MyOpenCVIF*> m_cvThread;

  void ThreadWorker(MyOpenCVIF* myCV, Mat& frame);
public:
  MyOpenCVProcessor();
  ~MyOpenCVProcessor(){}

  void Initialize();
  void ProcessFrame(Mat& frame);
};

#endif
