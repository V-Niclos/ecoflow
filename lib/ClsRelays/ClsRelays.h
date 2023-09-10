#ifndef CLSRELAYS_H
#define CLSRELAYS_H
#include "ClsRelayIrrigationPrg.h"
#include "ClsRelayOnOff.h"
#include "ClsFileSpiffs.h"
#include "Arduino.h"
#define RELAYS_IRRIGATION_COUNT 2
#define RELAYS_ONOF_COUNT 3
class ClsRelays
{
private:
  const uint m_relaysIrrigationCount = RELAYS_IRRIGATION_COUNT;
  const uint m_relaysOnOffCount =RELAYS_ONOF_COUNT;
  const double m_loopInterval = 1000;
  double m_loopIntervalPrevious = 0;
public:
  ClsRelays(/* args */);
  ~ClsRelays();
  ClsRelayIrrigationPrg m_RelaysIrrigation[RELAYS_IRRIGATION_COUNT];
  ClsRelayOnOff m_RelaysOnOff[RELAYS_ONOF_COUNT];
  void setup(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3,uint8_t pin4);
  void loop(double millisNow);
  String getJsonConfig(int idRelay);
  //void setJsonConfig(String JsonConfig);
  bool saveIrrigation(uint8_t relayId,String JsonConfig);
  bool readJsonConfig();

  void testRelays();
};
#endif
