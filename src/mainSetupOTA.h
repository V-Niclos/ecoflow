#ifndef MAINSETUPOTA_H
#define MAINSETUPOTA_H
#include "mainDefines.h"

#include <ArduinoOTA.h>
#include <ESPmDNS.h>

void fncMainSetupOTA()
{
  ArduinoOTA.setPort(3232);
  // We need a form field to assign the host name, then
  // the device can be accessed in the LAN as "$hostname.local", i.e. ecoflow.local
  ArduinoOTA.setHostname("ecoflow");

  // OTA updates can be protected with a password, we probably need a default
  // password, but also a field in the web interface to change it.
  ArduinoOTA.setPassword("ecoflow-ota-password");
  ArduinoOTA.begin();
}
#endif
