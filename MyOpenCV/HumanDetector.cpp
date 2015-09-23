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
  m_detector->detectMultiScale(image, objects, 1.11/*scaleFactor*/, 2/*minNeighbours*/, 0|CV_HAAR_SCALE_IMAGE, minObjSize, maxObjSize);
}


HumanDetector::HumanDetector(string p_cascadeFrontalFilename) :
  m_enabled(false),
  m_phase(0)
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
  Mat smallFrame;
  Mat grayFrame;
  vector<Rect> humans;

  if(m_phase == 0){
    resize(frame, smallFrame, Size(), 0.5, 0.5);
    cvtColor(smallFrame, grayFrame, COLOR_RGB2GRAY);
    m_detector->process(grayFrame);
  }
  else if (m_phase == 1){
    m_detector->getObjects(humans);
    m_humans.clear();
    for (size_t i = 0; i < humans.size(); i++){
      m_humans.push_back(humans[i]);
      m_humans[i] += m_humans[i].tl();
      m_humans[i] += m_humans[i].size();
    }
  }
  
  m_phase++;
  if(m_phase == 3) m_phase = 0;

  for (size_t i = 0; i < m_humans.size(); i++){
      rectangle(frame, m_humans[i], Scalar(0,255,0), 2);
  }
}
