#ifndef CLSRELAYS_H
#define CLSRELAYS_H
#include "ClsRelayIrrigationPrg.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "ClsRelayIrrigationPrg.h"
#include "RemoteDebug.h"
#include "ClsFileSpiffs.h"
#include "Arduino.h"
#define RELAYS_IRRIGATION_COUNT 5
extern RemoteDebug Debug;
class ClsRelays
{
private:
  const uint m_RelaysIrrigationPrgCount = RELAYS_IRRIGATION_COUNT;

  const double m_loopInterval = 1000;
  double m_loopIntervalPrevious = 0;
  void fncResetFactory();

public:
  ClsRelays(/* args */);
  ~ClsRelays();
  ClsRelayIrrigationPrg m_RelaysIrrigationPrg[RELAYS_IRRIGATION_COUNT];

  void setup(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool bForceResetPrg = false);
  void loop(DateTime now, bool isReset);
  String getJsonFromValuesConfig(int idRelay);
  // void setJsonConfig(String JsonConfig);
  bool saveIrrigation(uint8_t relayId, String JsonConfig);
  bool readJsonConfig();
};
#endif
