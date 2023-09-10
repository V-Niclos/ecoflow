#ifndef MAINSETUP_H
#define MAINSETUP_H
#include "mainDefines.h"

#include "mainSetupRelays.h"
#include "ClsNetworkConfig.h"
#include "mainSetupWebSrv.h"
#include "mainSetupWifi.h"
#include "mainSetupOTA.h"
#include "mainSetupTimeSun.h"
#include "mainSetupTasks.h"
#include "web_html_root.h"
#include "web_Html_confignet.h"
#include "web_css.h"
#include "web_js.h"
#include "web_svg.h"
#include "web_favicon.h"
void fncMainSetup()
{

  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Startinng");
  Serial.println();
  pinMode(g_pinIntLedBlue, OUTPUT);
  digitalWrite(g_pinIntLedBlue, HIGH);
  //todo comenta el forzado de pin reset


  fncMainSetupWifi();
  fncMainSetupTimeSun();
  fncMainSetupRelays();
  fncMainSetupWebSrv();
  fncMainSetupOTA();
}
#endif
