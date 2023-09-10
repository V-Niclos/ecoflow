#ifndef MAINSETUPWIFI_H
#define MAINSETUPWIFI_H
#include "mainDefines.h"
#include "ClsNetworkConfig.h"

void fncMainSetupWifi()
{
// g_NetworkConfig.setup(g_pinReset, false); //force reset by pin
  g_NetworkConfig.setup(g_pinReset, false); //true reset by software forced
  if (g_NetworkConfig.IsInternetAvailable())
  {
    g_TimeRtcNtp.fncReadNowNTP();
  }
}
#endif
