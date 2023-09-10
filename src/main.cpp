#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "mainDefines.h"
#include <SPIFFS.h>
#include "mainSetupRelays.h"
#include "mainSetupTimeSun.h"
#include "mainSetupWifi.h"
#include "mainSetupWebSrv.h"
#include "mainSetupOTA.h"
void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Startinng");
  Serial.println();
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
   delay(100);
}