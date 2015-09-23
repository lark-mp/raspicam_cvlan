#ifndef __HUMAN_DETECTOR_HPP
#define __HUMAN_DETECTOR_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "MyOpenCVIF.hpp"

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

class HumanDetector : public MyOpenCVIF
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

  virtual void ProcessFrame(Mat& frame);
};

#endif
