#ifndef MAINSETUPWIFI_H
#define MAINSETUPWIFI_H
#include "mainDefines.h"
#include "ClsNetworkConfig.h"

void fncMainSetupWifi(bool bResetFactoryNetwork)
{

  g_NetworkConfig.setup(bResetFactoryNetwork); // true force reset to default values

  debugI("MDNS starting as %s", g_NetworkConfig.gethostname());
  // Initialize mDNS
  if (!MDNS.begin(g_NetworkConfig.gethostname()))
  {
    // Set the hostname to "ecoflow.local"
    Serial.println("Error setting up MDNS responder! " + g_NetworkConfig.gethostname());
    while (1)
    {
      delay(1000);
    }
  }
  else
  {
    debugI("mDNS responder started as %s.local", g_NetworkConfig.gethostname().c_str());
    MDNS.addService("telnet", "tcp", 23);
  }
}
#endif
