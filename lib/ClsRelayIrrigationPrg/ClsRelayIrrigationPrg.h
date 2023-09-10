#ifndef CLSRELAYSRIEGOPRG_H
#define CLSRELAYSRIEGOPRG_H
#include <time.h>
#include <arduino.h>
#include "ClsFileSpiffs.h"
#include <ArduinoJson.h>
#include <RemoteDebug.h>
extern RemoteDebug Debug;

//-------------------------------------------
/* enum conversion
enum enumlist{CERO,UNO,DOS, TRES;}
int b = static_cast<int>(f);
enumList s2 = static_cast<enumList>(2);

-------------------------------------------------------------------------
Json config for html and save configv(Note: minutes in minutes,)
{"relayIrrigation": 
[
{"relayName": "Irrigation 2", "relayId": "1"}
],	
  "prg": 
  [
    {	"id": "0", "name": "prg 0", "mode": "1", "onOff": "0", "startHHMM": "12:35", "minutes": "6", "intervalDays": "2"},
    {	"id": "1", "name": "prg 1", "mode": "1", "onOff": "0", "startHHMM": "14:35", "minutes": "5", "intervalDays": "3"},
    { "id": "2", "name": "prg 2", "mode": "2", "onOff": "0", "startHHMM": "16:01", "minutes": "16", "intervalDays": "3"}]}
*/
//---------------------------------------------

class ClsRelayIrrigationPrg
{
public:
  enum ePrgMode
  {
    ePrgModeMANUAL,
    ePrgModeAUTO
  };
  enum eOnOff
  {
    eOnOff_OFF=0,
    eOnOff_ON=1
  };
  enum eIrrigation_OPENCLOSE
  {
     eIrrigation_CLOSE=LOW,
     eIrrigation_OPEN=HIGH
  };
  ClsRelayIrrigationPrg();
  ~ClsRelayIrrigationPrg();
  void loop();
  void setup(uint8_t RelayId, uint RelayPin, String RelayName, bool forceReset=false);
  void setupPrg_0_Auto(String prgName, eOnOff prgOnOff, String prgStartHHMM, uint8_t prgDuration, uint8_t prgIntervalDays);
  void setupPrg_1_Auto(String prgName, eOnOff prgOnOff, String prgStartHHMM, uint8_t prgDuration, uint8_t prgIntervalDays);
  void setupPrg_2_Manual(String prgName, eOnOff prgOnOff, String prgStartHHMM, uint8_t prgDuration);
  void setupPrg_0_DefaultAuto();
  void setupPrg_1_DefaultAuto();
  void setupPrg_2_DefaultManual();
  String getJson();
  bool   setJson(String jsonConfig);
  uint8_t getRelayIsOpen();
 // static const int m_PinRelayClose = HIGH;
 // static const int m_PinRelayOpen = LOW;
  uint8_t getPin();
  bool fncRelayConfigSave();
  void fncRelayConfigRead();
  void fncRelayConfigResetDefault();

String getHtmlStatus();

private:
  String m_RelayConfigFile = "";
  StaticJsonDocument<1024> m_JsonDoc;
  const ulong m_loopInterval = 10000;
  ulong m_loopIntervalPrevious = 0;
  uint m_RelayId = 0;
  uint m_RelayPin = 0;
  String m_RelayName = "";

  static const int m_IrrigationPrograms = 3;

  uint8_t ma_PrgId[m_IrrigationPrograms] = {0, 1, 2};
  String ma_PrgName[m_IrrigationPrograms] = {"", "", ""};
  ePrgMode ma_PrgMode[m_IrrigationPrograms] = {ePrgModeAUTO, ePrgModeAUTO, ePrgModeMANUAL};
  eOnOff ma_PrgOnOff[m_IrrigationPrograms] = {eOnOff_OFF, eOnOff_OFF, eOnOff_OFF}; // 0=of this programtion not never do it, 1=execution acording programation.
  String ma_PrgStartHHMM[m_IrrigationPrograms] = {"99:99", "99:99", "99:99"};      //"hh:mm"
  String ma_PrgStopHHMM[m_IrrigationPrograms] = {"99:99", "99:99", "99:99"};       //"hh:mm";
  uint8_t ma_PrgMinutes[m_IrrigationPrograms] = {0, 0, 0};
  uint8_t ma_PrgIntervalDays[m_IrrigationPrograms] = {0, 0, 0};
  time_t ma_PrgStartTime[m_IrrigationPrograms] = {0, 0, 0};
  time_t ma_PrgStopTime[m_IrrigationPrograms] = {0, 0, 0};
  eIrrigation_OPENCLOSE ma_PrgIsOpen[m_IrrigationPrograms] = {eIrrigation_CLOSE, eIrrigation_CLOSE, eIrrigation_CLOSE};
  void fncCalculateIrrigation(uint8_t prgId);
};
#endif