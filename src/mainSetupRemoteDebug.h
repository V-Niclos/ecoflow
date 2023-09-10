#ifndef MAINSETUP_REMOTEDEBUG_H
#define MAINSETUP_REMOTEDEBUG_H
#include "mainDefines.h"

#include <RemoteDebug.h>

void fncMainSetupRemoteDebug()
{
  Debug.begin("ecoflow");
  Debug.setResetCmdEnabled(true);  // Enable the reset command
  Debug.showProfiler(false);        // Profiler (Good to measure times, to optimize codes)
  Debug.showTime(true);
  Debug.showColors(true);          // Colors
  Debug.setSerialEnabled(true);    // Serial output (SerialDebug)
}
#endif