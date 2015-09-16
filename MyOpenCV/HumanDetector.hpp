#ifndef __HUMAN_DETECTOR_HPP
#define __HUMAN_DETECTOR_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "FPSCounter.hpp"

using namespace std;
using namespace cv;

class CascadeDetectorAdapter: public DetectionBasedTracker::IDetector
{
private:
  CascadeDetectorAdapter();
  Ptr<CascadeClassifier> m_detector;
public:
  CascadeDetectorAdapter(Ptr<CascadeClassifier> detector);
  virtual ~CascadeDetectorAdapter(){}

  void detect(const Mat &Image, vector<Rect> &objects);

};

class HumanDetector
{
private:
  string m_cascadeFrontalfilename;
  Ptr<DetectionBasedTracker::IDetector> m_mainDetector;
  Ptr<DetectionBasedTracker::IDetector> m_trackingDetector;
  
  DetectionBasedTracker::Parameters m_params;
  DetectionBasedTracker* m_detector;

  bool m_enabled;
  int m_phase;
  vector<Rect> m_humans;

  HumanDetector();
public:
  HumanDetector(string p_cascadeFrontalFilename);
  ~HumanDetector();

  void ProcessFrame(Mat& frame);

  static void* thread_function(void *arg) {
    HumanDetector* cls = (HumanDetector*)(((func_mat*)arg)->func);
    cls->ProcessFrame(*((func_mat*)arg)->frame);
    return NULL;
  }
};

#endif
