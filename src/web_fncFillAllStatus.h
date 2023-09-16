#ifndef WEB_FILLALLSTATUS
#include <Arduino.h>
#define WEB_FILLALLSTATUS
#include "mainDefines.h"
#include "ClsNetworkConfig.h"
#include "ClsTimeRtcNtp.h"
#include "ClsSunSetRise.h"
String fncFillAllStatus()
{
  // return "hola mundo desde mainSetupWebSrv::fncFillAllStatus";

  String htmlResult = "";
   htmlResult += "<br/>Date time" + g_TimeRtcNtp.TimeLocalHHMM() + " " + g_TimeRtcNtp.DateLocalYYYYMMDD();
   //htmlResult += " " g_TimeRtcNtp.NowString();
  htmlResult += g_Relays.m_RelaysIrrigation[0].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysIrrigation[1].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysOnOff[0].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysOnOff[1].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysOnOff[2].getHtmlStatus();
  return htmlResult;
}
#endif