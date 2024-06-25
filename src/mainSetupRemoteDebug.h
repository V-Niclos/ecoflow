#include "mainDefines.h"
#include <WiFi.h>
#include <DNSServer.h>
#include "ESPmDNS.h"
// https://github.com/JoaoLopesF/RemoteDebug/tree/master?tab=readme-ov-file#telnet
void fncSetupRemoteDebug()
{
  // Debug.begin(HOST_NAME, startingDebugLevel);



  Debug.setResetCmdEnabled(true); // Enable the reset command
  Debug.showProfiler(true);       // Profiler (Good to measure times, to optimize codes)
  Debug.showTime(true);
  Debug.setSerialEnabled(true); // Serial output (SerialDebug)
  Debug.showColors(true);       // Colors
  debugI(" Setup remote debug telnet IP= %s port 23,  hostname= %s.local ",WiFi.localIP().toString().c_str(), WiFi.getHostname());


}