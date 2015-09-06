#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "SystemMonitor.hpp"
#include <fstream>
#include <iomanip>

SystemMonitor::SystemMonitor()
{
  m_diffTime = 30;

  for(int i = 0;i < 4; i++){
    m_cpuInfo[i].preTick_=0;
    m_cpuInfo[i].preTime_=times(NULL);
    m_cpuInfo[i].m_lastRate="0%";
  }
}

void SystemMonitor::UpdateTemp()
{
  ifstream ifs("/sys/class/thermal/thermal_zone0/temp");
  if(ifs.fail()){
    fprintf(stderr, "Opening stat file failed.");
    return;
  }

  string temp;
  ifs >> temp;

  int itemp;
  itemp = atoi(temp.c_str());
  stringstream ss;
  ss << setw(4) << fixed << setprecision(1) << (float)itemp/1000;
  m_temp = ss.str();
}


string SystemMonitor::GetTemp()
{
  return m_temp;
}


void SystemMonitor::UpdateMemUsage()
{
  unsigned int cpuUsage=0;

  ifstream ifs("/proc/meminfo");
  if(ifs.fail()){
    fprintf(stderr, "Opening stat file failed.");
    return;
  }

  string name;
  int total;
  int avail;
  string postfix;

  ifs >> name >> total >> postfix;
  getline(ifs, name);
  getline(ifs, name);
  ifs >> name >> avail >> postfix;

  stringstream ss;
  ss << setw(5) << fixed << setprecision(1) << (float)(total-avail)/total << "%";
  m_memUsed = ss.str();
}


string SystemMonitor::GetMemUsage()
{
  return m_memUsed;
}


void SystemMonitor::UpdateCPUUsage()
{
  unsigned int cpuUsage=0;

  ifstream ifs("/proc/stat");
  string str;
  if(ifs.fail()){
    fprintf(stderr, "Opening stat file failed.");
    return;
  }

  for(int i=0; i < CPUNUMBER; i++){
    string buf;
    int usr, nice, sys;

    ifs >> buf >> usr >> nice >> sys;
    getline(ifs, str);

    clock_t now = times(NULL);

    if(m_cpuInfo[i].preTick_==0){
      m_cpuInfo[i].preTick_ = usr + nice + sys;
      m_cpuInfo[i].preTime_ = now;
      continue;
    }

    cpuUsage = ( (double)( usr + nice + sys - m_cpuInfo[i].preTick_ ) / ( now - m_cpuInfo[i].preTime_ ) )*100.0;

    m_cpuInfo[i].preTick_ = usr + nice + sys;
    m_cpuInfo[i].preTime_ = now;

    stringstream ss;
    ss << setw(3) << cpuUsage << "%";
    m_cpuInfo[i].m_lastRate = ss.str();
  }

  ifs.close();
}

string SystemMonitor::GetCPUUsage(int cpuNum)
{
  return m_cpuInfo[cpuNum].m_lastRate;
}

void SystemMonitor::ProcessFrame(Mat& frame)
{
  m_diffTime++;
  if(m_diffTime >= 30){
    UpdateCPUUsage();
    UpdateMemUsage();
    UpdateTemp();
    m_diffTime = 0;
  }
  putText(frame, "CPU:", Point(90,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetCPUUsage(0).c_str(), Point(150,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, ":", Point(220,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetCPUUsage(1).c_str(), Point(230,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetCPUUsage(2).c_str(), Point(290,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetCPUUsage(3).c_str(), Point(350,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetCPUUsage(4).c_str(), Point(410,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);

  putText(frame, "Mem:", Point(490,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetMemUsage().c_str(), Point(540,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);

  putText(frame, "Temp:", Point(480,470), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
  putText(frame, GetTemp().c_str(), Point(560,470), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
}

