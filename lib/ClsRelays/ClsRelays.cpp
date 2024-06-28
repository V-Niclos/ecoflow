
#include "ClsRelays.h"
ClsRelays::ClsRelays(/* args */)
{

}

ClsRelays::~ClsRelays()
{
}
void ClsRelays::setup(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool bResetFactoryRelays)
{
  // debugI("Relays pins: pin0: %u pin1:%u pin2:%u pin3:%u pin4:%u", pin0,pin1,pin2,pin3,pin4);
   // debugI(" call setup relay 0");
  m_RelaysIrrigationPrg[0].setup(0, pin0, "Irrigation 1", bResetFactoryRelays);
   // debugI(" call setup relay 1");
  m_RelaysIrrigationPrg[1].setup(1, pin1, "Irrigation 2", bResetFactoryRelays);
    // debugI(" call setup relay 2");
 // m_RelaysIrrigationPrg[2].setup(2, pin2, "Irrigation 3", bResetFactoryRelays);
     // debugI(" call setup relay 3");
  //m_RelaysIrrigationPrg[3].setup(3, pin3, "Irrigation 4", bResetFactoryRelays);
       // debugI(" call setup relay 4");
 // m_RelaysIrrigationPrg[4].setup(4, pin4, "Irrigation 5", bResetFactoryRelays);
       // debugI(" call setup relay end");
}
void ClsRelays::loop(DateTime now, bool isReset)
{
  m_RelaysIrrigationPrg[0].loop(now, isReset, false);
    m_RelaysIrrigationPrg[1].loop(now, isReset, false);
  // TODO HACER BUCLE A TODOS LOS RELES
  /*
    for (int i = 0; i < m_RelaysIrrigationPrgCount; i++)
    {
      m_RelaysIrrigationPrg[i].loop(now, isReset,false);
    }
    */
}

String ClsRelays::getJsonFromValuesConfig(int idRelay)
{

  return m_RelaysIrrigationPrg[idRelay].getJsonFromValues();
}
// todo

bool ClsRelays::saveIrrigation(uint8_t relayId, String jsonConfig)
{
  // // debugI("saveIrrigation %s", jsonConfig);
  m_RelaysIrrigationPrg[relayId].fncRelayConfigSave(jsonConfig);
  m_RelaysIrrigationPrg[relayId].fncRelayConfigRead();

  // TODO validate this return
  return true;
}
bool ClsRelays::readJsonConfig()
{
  m_RelaysIrrigationPrg[0].fncRelayConfigRead();
  m_RelaysIrrigationPrg[1].fncRelayConfigRead();
  m_RelaysIrrigationPrg[2].fncRelayConfigRead();
  m_RelaysIrrigationPrg[3].fncRelayConfigRead();
  m_RelaysIrrigationPrg[4].fncRelayConfigRead();

  // m_RelaysOnOff[0].fncRelayConfigRead();
  return true;
}