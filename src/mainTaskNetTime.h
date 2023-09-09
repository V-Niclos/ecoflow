#ifndef MAINTASKNETTIME_H
#define MAINTASKNETTIME_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "ClsTimeRtcNtp.h"
#include "mainDefines.h"

void g_MainTaskNetTime(void *pvParameters)
{

#ifdef DEBUG
  //Serial.println("");
  //Serial.print("g_TaskCore_1_LoopNetWork running on core ");
  //Serial.println(xPortGetCoreID());
#endif
  //g_LedsRing.begin();
  for (;;)
  {
      g_NetworkConfig.loop();   // if connection are lost try reconnect
      g_TimeRtcNtp.loop();
    
  }
}

#endif
