#ifndef MAINTASKRELAYS_H
#define MAINTASKRELAYS_H
#include "mainDefines.h"
void g_MainTaskRelays(void *pvParameters)
{

#ifdef DEBUG
  // Serial.println("");
  // Serial.print("g_TaskCore_1_LoopRelays running on core ");
  // Serial.println(xPortGetCoreID());
#endif
  for (;;)
  {
    g_TimeRtcNtp.loop();
    g_Relays.loop(millis());
  }
}
#endif