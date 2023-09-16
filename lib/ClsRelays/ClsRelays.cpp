#include <Arduino.h>
#include <ArduinoJson.h>
#include "ClsRelays.h"
#include "ClsRelayIrrigationPrg.h"
#include "ClsRelayOnOff.h"
ClsRelays::ClsRelays(/* args */)
{
}

ClsRelays::~ClsRelays()
{
}
void ClsRelays::setup(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
{
  //  void ClsRelayIrrigationPrg::setup(uint prgIdRelay, uint prgIdPrg,uint pin);
  // void setup(uint8_t RelayId, uint RelayPin, String RelayName);
 bool forceReset=false;  // setup( uint8_t id,  uint8_t Pin,   String Name ,uint8_t defaultOnOff);

  m_RelaysIrrigation[0].setup(0, pin0, "Irrigation 1",forceReset);
  m_RelaysIrrigation[1].setup(1, pin1, "Irrigation 2",forceReset);
  m_RelaysOnOff[0].setup(2, pin2, "OnOff 3", ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
  m_RelaysOnOff[1].setup(3, pin3, "OnOff 4", ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
  m_RelaysOnOff[2].setup(4, pin4, "OnOff 5", ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
}
void ClsRelays::loop(DateTime now,bool isReset)
{
  
  for (int i = 0; i < m_relaysIrrigationCount; i++)
  {
    m_RelaysIrrigation[i].loop(now, isReset);
  }
  for (int i = 0; i < m_relaysOnOffCount; i++)
  {
    m_RelaysOnOff[i].loop( isReset);
  }
}
void ClsRelays::testRelays()
{
  for (int i = 0; i < m_relaysIrrigationCount; i++)
  {
    digitalWrite(m_RelaysIrrigation[i].getPin(), ClsRelayIrrigationPrg::eIrrigation_OPEN);
    delay(1000);
  }
  for (int i = 0; i < m_relaysOnOffCount; i++)
  {
    digitalWrite(m_RelaysIrrigation[i].getPin(), ClsRelayIrrigationPrg::eIrrigation_CLOSE);
    delay(1000);
  }
  for (int i = 0; i < m_relaysOnOffCount; i++)
  {
    digitalWrite(m_RelaysOnOff[i].getPin(), ClsRelayOnOff::eOnOff_OPENCLOSE_OPEN);
    delay(1000);
  }
  for (int i = 0; i < m_relaysOnOffCount; i++)
  {
    digitalWrite(m_RelaysOnOff[i].getPin(), ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
    delay(1000);
  }
}
String ClsRelays::getJsonConfig(int idRelay)
{
  switch (idRelay)
  {
  case 0:
    return m_RelaysIrrigation[idRelay].getJson();
    break;
  case 1:
    return m_RelaysIrrigation[idRelay].getJson();
    break;
  case 2:
    return m_RelaysOnOff[idRelay].getJson();
    break;
  case 3:
    return m_RelaysOnOff[idRelay].getJson();
    break;
  case 4:
    return m_RelaysOnOff[idRelay].getJson();
    break;
  default:
    break;
  }

  return "NaN";
}
// todo

bool ClsRelays::saveIrrigation(uint8_t relayId, String jsonConfig)
{
   m_RelaysIrrigation[relayId].setJson(jsonConfig);
   // TODO validate this return
   return true;
}
bool ClsRelays::readJsonConfig()
{
  m_RelaysIrrigation[0].fncRelayConfigRead();
  m_RelaysIrrigation[1].fncRelayConfigRead();
 // m_RelaysOnOff[0].fncRelayConfigRead();
  return true;
}