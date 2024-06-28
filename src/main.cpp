#include <Arduino.h>
#include "mainDefines.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClientSecure.h>
#include <AsyncTCP.h>
#include <ElegantOTA.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <SPIFFS.h>
#include "mainSetupRelays.h"
#include "mainSetupTimeSun.h"
#include "mainSetupWifi.h"
#include "mainSetupWebSrv.h"
#include "mainSetupRemoteDebug.h"
#include "mainSetupOta.h"
#include "mainFlowSensor.h"
#include "mainResetPressed.h"
#include "mainSetupThingSpeak.h"
void setup()
{

  Serial.begin(SERIAL_BAUDRATE);
  pinMode(g_pinLedFlash, OUTPUT);
  digitalWrite(g_pinLedFlash, HIGH_INT_LED);
  pinMode(g_pinIntLedRed, OUTPUT);
  digitalWrite(g_pinIntLedRed, HIGH_INT_LED);

  Serial.println("----------------------------- SETUP START");
  ClsFileSpiffs::begin();
  fncSetupRemoteDebug();
  fncMainSetupWifi(g_bResetFactoryNetwork);
  fncMainSetupThingSpeak();
  fncMainSetupOTA();
  fncMainSetupTimeSun();
  fncMainSetupRelays(g_bResetFactoryRelays);
  fncMainSetupWebSrv();
  fncFlow_Setup();

  digitalWrite(g_pinLedFlash, LOW_INT_LED);
  digitalWrite(g_pinIntLedRed, LOW_INT_LED);

  Serial.println("----------------------------- SETUP END");
}

void loop()
{
  DateTime now = g_TimeRtcNtp.nowDateTime_lastRead();
  g_NetworkConfig.loop(false);
  g_TimeRtcNtp.loop(true);
  g_Relays.loop(now, false);
  fncFlow_Loop();
  g_ThingSpeak.loop();
  ArduinoOTA.handle();
  Debug.handle();
}