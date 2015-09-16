#include "MyOpenCVIF.hpp"
#include <pthread.h>

MyOpenCVIF::MyOpenCVIF() :
  m_FPSCounter(),
  m_humanDetector("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml")
{
}


void MyOpenCVIF::ProcessFrame(Mat& frame)
{
  pthread_t th1;
  pthread_t th2;
  pthread_t th3;

  m_frame = frame;

  func_mat mat = {(void *)&m_FPSCounter, &m_frame};
  func_mat mat2 = {(void *)&m_systemMonitor, &m_frame};
  func_mat mat3 = {(void *)&m_humanDetector, &m_frame};

  pthread_create(&th3, NULL, HumanDetector::thread_function, (void *)&mat3);
  pthread_create(&th2, NULL, SystemMonitor::thread_function, (void *)&mat2);
  //pthread_create(&th1, NULL, FPSCounter::thread_function, (void *)&mat);

  m_FPSCounter.ProcessFrame(m_frame);
  //m_systemMonitor.ProcessFrame(m_frame);
  //m_humanDetector.ProcessFrame(m_frame);
  m_HUD.ProcessFrame(m_frame);

  //pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);

  frame = m_frame;
}
