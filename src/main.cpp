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
#include "ClsFileSpiffs.h"

RemoteDebug Debug;

void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Startinng");
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

}

//---------------------------------------------------------

//----------------------------------------------------------



void loop()
{

  ArduinoOTA.handle();
  g_TimeRtcNtp.loop();
  g_Relays.loop(millis());
  g_NetworkConfig.loop();   // if connection are lost try reconnect
  Debug.handle();

  delay(100);
  yield();
}