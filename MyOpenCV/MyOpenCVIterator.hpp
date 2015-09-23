#ifndef __OPENCV_ITERATOR_HPP
#define __OPENCV_ITERATOR_HPP

#include <opencv2/core/core.hpp>
#include "MyOpenCVIF.hpp"

using namespace std;
using namespace cv;

class MyOpenCVIterator
{
private:
  vector<MyOpenCVIF*> m_cvMain;
  vector<MyOpenCVIF*> m_cvThread;

  void ThreadWorker(MyOpenCVIF* myCV, Mat& frame);
public:
  MyOpenCVIterator();
  ~MyOpenCVIterator(){}

  void Initialize();
  void ProcessFrame(Mat& frame);
};

#endif
