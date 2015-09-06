#include <vector>
#include <opencv2/imgproc/imgproc.hpp>

#include "HumanDetector.hpp"

CascadeDetectorAdapter::CascadeDetectorAdapter(Ptr<CascadeClassifier> detector) :
  IDetector(),
  m_detector(detector)
{
  CV_Assert(detector);
}

void CascadeDetectorAdapter::detect(const Mat &image, vector<Rect> &objects)
{
  m_detector->detectMultiScale(image, objects, 1.1/*scaleFactor*/, 2/*minNeighbours*/, 0|CV_HAAR_SCALE_IMAGE, minObjSize, maxObjSize);
}


HumanDetector::HumanDetector(string p_cascadeFrontalFilename) :
  m_enabled(false)
{
  m_cascadeFrontalfilename = p_cascadeFrontalFilename;
  Ptr<CascadeClassifier> cascade = makePtr<CascadeClassifier>(m_cascadeFrontalfilename);
  m_mainDetector = makePtr<CascadeDetectorAdapter>(cascade);
	
  cascade = makePtr<CascadeClassifier>(m_cascadeFrontalfilename);
  m_trackingDetector = makePtr<CascadeDetectorAdapter>(cascade);
	
  m_detector = new DetectionBasedTracker(m_mainDetector, m_trackingDetector, m_params);

  if (m_detector->run()){
    m_enabled = true;
  } else {
      printf("Error: Human detector initialization failed!\n");
  }
}

HumanDetector::~HumanDetector()
{
  m_detector->stop();
  delete m_detector;
}

void HumanDetector::ProcessFrame(Mat& frame)
{
  if(!m_enabled) return;
  Mat grayFrame;
  vector<Rect> humans;

  cvtColor(frame, grayFrame, COLOR_RGB2GRAY);
  m_detector->process(grayFrame);
  m_detector->getObjects(humans);
  
  for (size_t i = 0; i < humans.size(); i++){
      rectangle(frame, humans[i], Scalar(0,255,0));
  }
}
