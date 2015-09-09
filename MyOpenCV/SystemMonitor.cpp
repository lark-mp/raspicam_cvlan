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
  ss << setw(4) << fixed << setprecision(1) << (float)(total-avail)/total << "%";
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

  string topStatus = "CPU:"+GetCPUUsage(0)+":"
    +GetCPUUsage(1)+" "
    +GetCPUUsage(2)+" "
    +GetCPUUsage(3)+" "
    +GetCPUUsage(4)+" "
    +"Mem:"+GetMemUsage();
  putText(frame, topStatus.c_str(), Point(90,20), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);

  string bottomStatus = "Temp:"+GetTemp();
  putText(frame, bottomStatus.c_str(), Point(480,470), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,200,0), 2, CV_AA);
}

