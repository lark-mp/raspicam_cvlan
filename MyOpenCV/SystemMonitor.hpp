#ifndef __SYSTEM_MONITOR_H__
#define __SYSTEM_MONITOR_H__

#include <opencv2/core/core.hpp>
#include <sys/times.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include "MyOpenCVIF.hpp"

using namespace std;
using namespace cv;

class SystemMonitor : public MyOpenCVIF
{
 private:
  string GetCPUUsage(int cpuNum);
  void UpdateCPUUsage();

  string GetMemUsage();
  void UpdateMemUsage();

  string GetTemp();
  void UpdateTemp();

  int m_diffTime;
  static const int CPUNUMBER = 4 + 1;

  struct CPUData{
    int preTick_;
    clock_t preTime_;
    string m_lastRate;
  };
  CPUData m_cpuInfo[5];

  string m_memUsed;

  string m_temp;
 public:
  SystemMonitor();
  ~SystemMonitor(){}

  virtual void ProcessFrame(Mat& frame);
};


#endif
