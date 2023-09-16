#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClientSecure.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <RemoteDebug.h>

#include "mainDefines.h"
#include <SPIFFS.h>
#include "mainSetupRelays.h"
#include "mainSetupTimeSun.h"
#include "mainSetupWifi.h"
#include "mainSetupWebSrv.h"
#include "mainSetupOTA.h"
#include "mainSetupRemoteDebug.h"
#include "mainResetPressed.h"
#include "ClsFileSpiffs.h"

RemoteDebug Debug;

void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Starting ecoflow setup");
  Serial.println();

  // We need to do a basic WiFi begin because the RemoteDebug tries to access networking
  WiFi.begin();
  // Then we enable the remote debug, to enable use of debug output in the next modules.
  fncMainSetupRemoteDebug();

  ClsFileSpiffs::begin();

  pinMode(g_pinIntLedBlue, OUTPUT);
  digitalWrite(g_pinIntLedBlue, HIGH);
  fncMainSetupWifi();
  fncMainSetupTimeSun();
  fncMainSetupRelays();
  fncMainSetupWebSrv();
  fncMainSetupOTA();

  debugI("Setup done");
}

//---------------------------------------------------------

//----------------------------------------------------------

void loop()
{
  isResetPressed();
  ArduinoOTA.handle();
  g_TimeRtcNtp.loop();
  g_NetworkConfig.loop(g_IsReset);   // if connection are lost try reconnect
  g_Relays.loop(g_TimeRtcNtp.nowDateTime(),g_IsReset);
  Debug.handle();
  delay(10);
  yield();
}