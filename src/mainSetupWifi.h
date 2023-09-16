#ifndef MAINSETUPWIFI_H
#define MAINSETUPWIFI_H
#include "mainDefines.h"
#include "ClsNetworkConfig.h"

void fncMainSetupWifi()
{
// g_NetworkConfig.setup(g_pinReset, false); //force reset by pin
  g_NetworkConfig.setup(); //true reset by software forced
}
#endif
