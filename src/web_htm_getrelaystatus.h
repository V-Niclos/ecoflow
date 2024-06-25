#ifndef WEB_HTMLGETRELAYSTATUS_H
#define WEB_HTMLGETRELAYSTATUS_H
#include <Arduino.h>
#include "mainDefines.h"
#include "ClsNetworkConfig.h"
#include "ClsTimeRtcNtp.h"
#include "ClsSunset.h"
String fncHtmlGetRelayStatus(uint8_t idRelay)
{
  // return "hola mundo desde mainSetupWebSrv::fncHtmlRelayIdStatus";

  String htmlResult = "";

  htmlResult += "<br/>Date time  " + g_TimeRtcNtp.NowString();
  htmlResult += "<br/>Sunrise: " + g_TimeRtcNtp.SunSetRise.getSunriseHHMM();
  htmlResult += "<br/>Sunset: " + g_TimeRtcNtp.SunSetRise.getSunsetHHMM();

  htmlResult += g_Relays.m_RelaysIrrigationPrg[idRelay].getHtmlStatus();
  return htmlResult;
}
#endif