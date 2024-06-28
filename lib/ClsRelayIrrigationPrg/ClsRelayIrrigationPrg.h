#ifndef CLSRELAYSriegoPRG_H
#define CLSRELAYSriegoPRG_H
#include <time.h>
#include "RTClib.h"
#include <arduino.h>
#include "ClsFileSpiffs.h"
#include <ArduinoJson.h>
#include "RemoteDebug.h"

class ClsRelayIrrigationPrg
{
public:
  const uint32_t m_loopIntervalSecodtime = 30;
  uint32_t m_loopIntervalSecodtimePrevious = 0;

  enum eOPENCLOSE
  {
    eOPENCLOSE_OPEN = 1,
    eOPENCLOSE_CLOSE = 0
  }; // LOW HIGHT

  ClsRelayIrrigationPrg();
  ~ClsRelayIrrigationPrg();
  void loop(DateTime now, bool forceResetFactory, bool bWithoutWaiting);
  void setup(uint8_t relayId, uint relayPin, String relayName, bool bResetFactoryRelays);

  void setupPrg_Auto(String prgAuto_Description, bool prgAuto_IsActive, String PrgAuto_StartHHMM, uint8_t prgAuto_Minutes, uint8_t prgAuto_IntervalDays);

  void setupPrg_Manual(DateTime prgManual_now, uint8_t prgManualMinutes);

  void setupPrg_ResetFactory();

  String getJsonFromValues();
  bool setJsonToValues(String jsonConfig);

  uint8_t getRelayIsOpen();

  uint8_t getPin();
  bool fncRelayConfigSave(String jsonConfig);
  void fncRelayConfigRead();
  void debug(String sFrom);

  String DateTimeToString_HHMM(DateTime date);
  String DateTimeToString_YYMMDD(DateTime date);
  String DateTimeToString_YYMMDD_HHMM(DateTime date);
  String DateTimeToString_YYMMDD_HHMMSS(DateTime date);
  String getHtmlStatus();

  String get_RelayMessage();

private:
  DateTime m_time0 = time(0);
  String m_RelayConfigFile = "";
  JsonDocument m_JsonDoc;
  uint8_t m_RelayId = 0;
  uint8_t m_RelayPin = 0;
  String m_RelayName = "";
  String m_RelayMessage = ""; // last message filled in loop, like "Error...., OK, starte by manual option ..."
  DateTime calculate_DT_Last_Driping = time(0);
   uint32_t m_Litres_total = 0;
  uint32_t m_Litres_today = 0;

  bool m_PrgAuto_IsDriping = false;
  bool m_PrgAuto_IsDripingBefore = false;
  bool m_PrgAuto_IsActive = false;
  bool m_PrgAuto_Start_IsFirst = false;
  String m_PrgAuto_Description = "";
  String m_PrgAuto_StartHHMM = "00:00";
  u_int8_t m_PrgAuto_Start_iHH = 0;
  u_int8_t m_PrgAuto_Start_iMM = 0;
  uint8_t m_PrgAuto_Minutes = 0;
  uint8_t m_PrgAuto_IntervalDays = 0; // 0=nunca, 1=cada dia, 2=dias alternos

  uint32_t m_PrgAuto_Start_Counter = 0;      // flag to know is first calulate datetime of prgAuto and knot How many times driping auto
  DateTime m_prgAuto_Start_LastDT = m_time0; // Save for calculate next datetime of prgAuto

  String m_PrgManual_Description = "";
  bool m_PrgManual_IsActive = false;
  bool m_PrgManual_IsDriping = false;
  bool m_PrgManual_IsDripingBefore = false;
  String m_PrgManual_StartHHMM = "00:00";
  uint8_t m_PrgManual_Minutes = 0;

  DateTime m_Calculate_Start_DT = m_time0;
  DateTime m_Calculate_Stop_DT = m_time0;

  bool m_Calculate_IsInRange = false;
  bool m_Calculate_IsInDriping = false;
  bool fncCalculate_Auto(DateTime now);
  bool fncCalculate_Manual(DateTime now);
  // bool fncCalcualteStop(DateTime now);
  bool fncCalculateIsInRange(String from, bool isActive, DateTime dt_value, DateTime dt_start, DateTime dt_stop);
  String fncHHMM_EmptyBadValue(String HHMM);
  String fncSplitString(String data, char separator, int index);

 
};
#endif