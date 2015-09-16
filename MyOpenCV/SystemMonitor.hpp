#ifndef __SYSTEM_MONITOR_H__
#define __SYSTEM_MONITOR_H__

#include <opencv2/core/core.hpp>
#include <sys/times.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include "FPSCounter.hpp"

using namespace std;
using namespace cv;

class SystemMonitor
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

  void ProcessFrame(Mat& frame);

  static void* thread_function(void *arg) {
    SystemMonitor* cls = (SystemMonitor*)(((func_mat*)arg)->func);
    cls->ProcessFrame(*((func_mat*)arg)->frame);
    return NULL;
  }
};


#endif
