#ifndef MAINSETUPOTA_H
#define MAINSETUPOTA_H

#include <ArduinoOTA.h>
#include <ESPmDNS.h>

void fncMainSetupOTA()
{
  // debugI("ARDUINO OTA -----------------------");
  ArduinoOTA.setPort(3232);
  ArduinoOTA.setHostname("riego");
  ArduinoOTA.setPassword((const char *)"riego1234");
  ArduinoOTA.onStart([]()
                     { Serial.println("Ota Start"); });
  ArduinoOTA.onEnd([]()
                   { Serial.println("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Ota Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Ota Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Ota Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Ota Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("Ota End Failed"); });
  ArduinoOTA.begin();


  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print(  Serial.println("Ota Hostname:"+ArduinoOTA.getHostname()));
    Serial.println("---------------- Ota Ready");
}

#endif
