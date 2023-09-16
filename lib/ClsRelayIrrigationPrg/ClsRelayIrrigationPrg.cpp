#include "ClsRelayIrrigationPrg.h"
#include "time.h"
ClsRelayIrrigationPrg::ClsRelayIrrigationPrg(/* args */)
{
}
ClsRelayIrrigationPrg::~ClsRelayIrrigationPrg()
{
}
void ClsRelayIrrigationPrg::setup(uint8_t relayId, uint relayPin, String relayName, bool forceReset)
{
    m_RelayId = relayId;
    m_RelayPin = relayPin;
    m_RelayName = relayName;
    m_RelayConfigFile = "/irrigation" + String(relayId) + ".json";
    pinMode(m_RelayPin, OUTPUT);
    digitalWrite(m_RelayPin, m_PinRelayClose);
    if (forceReset)
    {
        fncResetFactory();
    }

    // Serial.print("ClsRelayIrrigationPrg::setup m_RelayId" + String(m_RelayId) + " m_RelayId" + String(m_RelayId) + " m_RelayName=" + m_RelayName+"file config="+m_RelayConfigFile);
    fncRelayConfigRead();
}
void ClsRelayIrrigationPrg::loop(DateTime now,bool isReset)
{
      if (isReset)
    {
        fncResetFactory();
        return;
    }
    long millisNow = millis();
    if (millisNow < m_loopIntervalPrevious)
    {
        m_loopIntervalPrevious = 0;
    }
    if (millisNow - m_loopIntervalPrevious < m_loopInterval)
    {
        return;
    }
    m_loopIntervalPrevious = millisNow;

  
    // if 1 of 3  calculate programation say is time of
    // irrigation then irrigation is true
    // if all calcualte programtion are false then false
    bool shouldBeOpen = false;
    for (int prgId = 0; prgId < 2; prgId++)
    {
        if (isInRangeIrrigation(prgId, now))
        {
            shouldBeOpen = true;
        }
    }
    if (shouldBeOpen)
    {
        {
            digitalWrite(m_RelayPin, eIrrigation_OPEN);
        }
    }
    else
    {
        digitalWrite(m_RelayPin, eIrrigation_CLOSE);
    }
}

//=================================================================================0
//=================================================================================0
//=================================================================================0
//=================================================================================0
//=================================================================================0

bool ClsRelayIrrigationPrg::isInRangeIrrigation(uint8_t prgId, DateTime now)
{
    // TODO verificar error crash con rtclib
    return true;
    bool bResult = false;
    uint8_t hh = 0;
    uint8_t mm = 0;

    hh = ma_PrgStartHHMM[prgId].substring(0, 2).toInt();
    mm = ma_PrgStartHHMM[prgId].substring(3, 2).toInt();
#ifdef DEBUG
    Serial.print(ma_PrgStartHHMM[prgId]);
    Serial.print(" conver toint  ");
    Serial.print(hh);
    Serial.print(" ");
    Serial.println(mm);
#endif
    // maybe error in parameter
    if (hh > 24)
        return false;
    if (mm > 59)
        return false;
    if (ma_PrgMinutes[prgId] > 59)
    {
        ma_PrgMinutes[prgId] = 0;
        return false;
    }

    return false;
    // https://arduwiki.perut.org/index.php/DateTime
    DateTime datetimeStart(now.year(), now.month(), now.day(), hh, mm, 0);
    DateTime datetimeEnd = datetimeStart + TimeSpan(0, 0, ma_PrgMinutes[prgId], 0);

#ifdef DEBUG
    Serial.print("now");
    Serial.println(DateTimeToString_YYMMDD_HHMM(now));
    Serial.print("PrgMinutes");
 Serial.println( ma_PrgMinutes[prgId]);
 Serial.print("datetimeStart ");
 Serial.println(DateTimeToString_YYMMDD_HHMM(datetimeStart));
 Serial.print("datetimeEnd");
 Serial.println(DateTimeToString_YYMMDD_HHMM(datetimeEnd));

#endif
 ma_PrgStartTime[prgId] = datetimeStart;
 ma_PrgStopTime[prgId] = datetimeEnd;

 if (now > ma_PrgStartTime[prgId] && now < ma_PrgStopTime[prgId])
 {
     bResult = true;
 }
 else
 {
     bResult = false;
 }
 // if this programition are in off force not irrigation until next acctivation
 if (ma_PrgOnOff[prgId] == eOnOff_OFF)
     return bResult;
}
//=================================================================================0
//=================================================================================0
//=================================================================================0
//=================================================================================0
void ClsRelayIrrigationPrg::setupPrg_0_Auto(String prgName, eOnOff prgOnOff, String prgStartHHMM, uint8_t prgDuration, uint8_t prgIntervalDays)
{
 uint8_t prgId = 0;
 ma_PrgId[prgId] = prgId;
 ma_PrgName[prgId] = prgName;
 ma_PrgMode[prgId] = ePrgModeAUTO;
 ma_PrgOnOff[prgId] = prgOnOff;
 ma_PrgStartHHMM[prgId] = prgStartHHMM;
 ma_PrgMinutes[prgId] = prgDuration;
 ma_PrgIntervalDays[prgId] = prgIntervalDays;
 // fncCalculateIrrigation(prgId);
}
void ClsRelayIrrigationPrg::setupPrg_1_Auto(String prgName, eOnOff prgOnOff, String prgStartHHMM, uint8_t prgDuration, uint8_t prgIntervalDays)
{

 uint8_t prgId = 1;
 ma_PrgId[prgId] = prgId;
 ma_PrgName[prgId] = prgName;
 ma_PrgMode[prgId] = ePrgModeAUTO;
 ma_PrgOnOff[prgId] = prgOnOff;
 ma_PrgStartHHMM[prgId] = prgStartHHMM;
 ma_PrgMinutes[prgId] = prgDuration;
 ma_PrgIntervalDays[prgId] = prgIntervalDays;
 // fncCalculateIrrigation(prgId);
}
void ClsRelayIrrigationPrg::setupPrg_2_Manual(String prgName, eOnOff prgOnOff, String prgStartHHMM, uint8_t prgDuration)
{

 uint8_t prgId = 1;
 ma_PrgId[prgId] = prgId;
 ma_PrgName[prgId] = prgName;
 ma_PrgMode[prgId] = ePrgModeAUTO;
 ma_PrgOnOff[prgId] = prgOnOff;
 ma_PrgStartHHMM[prgId] = prgStartHHMM;
 ma_PrgMinutes[prgId] = prgDuration;
 ma_PrgIntervalDays[prgId] = 0;
 // fncCalculateIrrigation(prgId);
}
void ClsRelayIrrigationPrg::fncResetFactory()
{
 setupPrg_0_DefaultAuto();
 setupPrg_1_DefaultAuto();
 setupPrg_2_DefaultManual();
 fncRelayConfigSave();
}
void ClsRelayIrrigationPrg::setupPrg_0_DefaultAuto()
{
 int i = 0;

 ma_PrgName[i] = "Prg 0";
 ma_PrgMode[i] = ePrgModeAUTO;
 ma_PrgOnOff[i] = eOnOff_OFF;  // 0=of this programtion not never do it, 1=execution acording programation.
 ma_PrgStartHHMM[i] = "99:99"; //"hh:mm"
 ma_PrgStopHHMM[i] = "99:99";  //"hh:mm";
 ma_PrgMinutes[i] = 0;
 ma_PrgIntervalDays[i] = 0;
 time_t time0 = time(0);
 ma_PrgStartTime[i] = time0;
 ma_PrgStopTime[i] = time0;
}
void ClsRelayIrrigationPrg::setupPrg_1_DefaultAuto()
{
 int i = 1;

 ma_PrgName[i] = "Prg 1";
 ma_PrgMode[i] = ePrgModeAUTO;
 ma_PrgOnOff[i] = eOnOff_OFF;  // 0=of this programtion not never do it, 1=execution acording programation.
 ma_PrgStartHHMM[i] = "99:99"; //"hh:mm"
 ma_PrgStopHHMM[i] = "99:99";  //"hh:mm";
 ma_PrgMinutes[i] = 0;
 ma_PrgIntervalDays[i] = 0;
 time_t time0 = time(0);
 ma_PrgStartTime[i] = time0;
 ma_PrgStopTime[i] = time0;
}
void ClsRelayIrrigationPrg::setupPrg_2_DefaultManual()
{
 int i = 2;
 ma_PrgName[i] = "Prg 2";
 ma_PrgMode[i] = ePrgModeMANUAL;
 ma_PrgOnOff[i] = eOnOff_OFF;  // 0=of this programtion not never do it, 1=execution acording programation.
 ma_PrgStartHHMM[i] = "99:99"; //"hh:mm"
 ma_PrgStopHHMM[i] = "99:99";  //"hh:mm";
 ma_PrgMinutes[i] = 0;
 ma_PrgIntervalDays[i] = 0;
 time_t time0 = time(0);
 ma_PrgStartTime[i] = time0;
 ma_PrgStopTime[i] = time0;
}

uint8_t ClsRelayIrrigationPrg::getRelayIsOpen()
{
 if (digitalRead(m_RelayPin) == m_PinRelayOpen)
 {
     return 1;
 }
 else
 {
     return 0;
 }
}
uint8_t ClsRelayIrrigationPrg::getPin() { return m_RelayPin; }
String ClsRelayIrrigationPrg::getJson()
{
 String result = "{\"relayIrrigation\": [{";
 result += "\"id\":\"" + String(m_RelayId) + "\", ";
 result += "\"name\":\"" + m_RelayName + "\"";
 result += "}],";
 result += "\"prg\":[";
 bool isFirst = true;
 for (uint8_t id = 0; id < 3; id++)
 {
     if (!isFirst)
     {
         result += ", ";
     }
     else
     {
         isFirst = false;
     }
     result += "{";
     result += ("\"id\":\"" + String(ma_PrgId[id]) + "\", ");
     result += ("\"name\":\"" + String(ma_PrgName[id]) + "\", ");
     result += ("\"mode\":\"" + String(ma_PrgMode[id]) + "\", ");
     result += ("\"onOff\":\"" + String(ma_PrgOnOff[id]) + "\", ");
     result += ("\"startHHMM\":\"" + ma_PrgStartHHMM[id] + "\", ");
     result += ("\"PrgStop\":\"" + ma_PrgStopHHMM[id] + "\", ");
     result += ("\"minutes\":\"" + String(ma_PrgMinutes[id]) + "\", ");
     result += ("\"intervalDays\":\"" + String(ma_PrgIntervalDays[id]) + "\", ");
     result += ("\"PrgIsOpen\":\"" + String(ma_PrgIsOpen[id]) + "\""); // Don't need, buy is good for fill html
     result += "}";
 }
 result += "]}";
 // Serial.println(result);
 return result;
}

bool ClsRelayIrrigationPrg::setJson(String jsonConfig)
{

  // debugI("ClsRelayIrrigationPrg::setJson jsonConfig=%s", jsonConfig.c_str());
 // Serial.println(jsonConfig);
 DeserializationError error = deserializeJson(m_JsonDoc, jsonConfig);

 // Test if parsing succeeds.
 if (error)
 {
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.f_str());
     return false;
 }
 m_RelayId = m_JsonDoc["relayIrrigation"]["RelayId"].as<int>();
 m_RelayName = m_JsonDoc["relayIrrigation"]["name"].as<int>();

 /* casting enum
 int b = static_cast<int>(f);
 enumList s2 = static_cast<enumList>(2);

   */
 int iTemp = 0;
 for (uint prgId; prgId < 3; prgId++)
 {

     ma_PrgId[prgId] = m_JsonDoc["prg"][prgId]["id"].as<uint8_t>();
     ma_PrgName[prgId] = m_JsonDoc["prg"][prgId]["name"].as<String>();

     iTemp = m_JsonDoc["prg"][prgId]["mode"].as<int>();
     ma_PrgMode[prgId] = static_cast<ClsRelayIrrigationPrg::ePrgMode>(iTemp);

     iTemp = m_JsonDoc["prg"][prgId]["onOff"].as<int>();
     ma_PrgOnOff[prgId] = static_cast<ClsRelayIrrigationPrg::eOnOff>(iTemp);

     ma_PrgStartHHMM[prgId] = m_JsonDoc["prg"][prgId]["startHHMM"].as<String>();
     ma_PrgMinutes[prgId] = m_JsonDoc["prg"][prgId]["minutes"].as<uint8_t>();
     ma_PrgIntervalDays[prgId] = m_JsonDoc["prg"][prgId]["intervalDays"].as<uint8_t>();
 }
 return fncRelayConfigSave();
}
bool ClsRelayIrrigationPrg::fncRelayConfigSave()
{

    String jsonConfig=getJson();
     // debugI("/ClsRelayIrrigationPrg::fncRelayConfigSave() file=%s  jsonConfig= %s", m_RelayConfigFile.c_str(), jsonConfig.c_str());
 return ClsFileSpiffs::fileWrite(m_RelayConfigFile, jsonConfig);
}

void ClsRelayIrrigationPrg::fncRelayConfigRead()
{

 // Serial.println("ClsRelayIrrigationPrg::fncRelayConfigRead" +m_RelayConfigFile );
 if (!ClsFileSpiffs::fileExist(m_RelayConfigFile))
 {
     // if not exist previous config
     // set default values and save
     setupPrg_0_DefaultAuto();
     setupPrg_1_DefaultAuto();
     setupPrg_2_DefaultManual();
     fncRelayConfigSave();
 }
 String jsonConfig = ClsFileSpiffs::fileRead(m_RelayConfigFile);
  //  debugI("ClsRelayIrrigationPrg::fncRelayConfigRead()  jsonConfig=%s", jsonConfig.c_str());
 setJson(jsonConfig);
}

String ClsRelayIrrigationPrg::getHtmlStatus()
{
 String result = "<p>";
 result += "<p> <b>Relay Irrigation:" + String(m_RelayId) + " " + m_RelayName + "</b>";

 if (getRelayIsOpen())
 {
     result += "<span class=\"led green\"></span>";
 }
 else
 {
     result += "<span class=\"led red\"></span>";
 }

 for (uint8_t idPrg = 0; idPrg < 3; idPrg++)
 {

     result += "<br/><b> PrgId=" + ma_PrgId[idPrg];
     result += " Name=" + ma_PrgName[idPrg] + "</b><br/>";

     if (ma_PrgMode[idPrg] == ePrgModeAUTO)
     {
         result += "Mode= Automatic";
     }
     if (ma_PrgMode[idPrg] == ePrgModeMANUAL)
     {
         result += "Mode= Manual";
     }
     result += "<br/> On Off=" + String(ma_PrgOnOff[idPrg]);
     result += "<br/> Minutes= " + String(ma_PrgMinutes[idPrg]);
     result += "<br/> Interval days= " + String(ma_PrgIntervalDays[idPrg]);
     result += "<br/> Start time" + ma_PrgStartHHMM[idPrg];
     result += "<br/> Stop time" + ma_PrgStartHHMM[idPrg];
     result += "</p>";
 }
 result += "</p>";
 Serial.println(result);
 return result;
}

String ClsRelayIrrigationPrg::DateTimeToString_HHMM(DateTime date)
{
 char time_buf[6]; // size big enough
 sprintf(time_buf, "%02u:%02u: ", date.hour(), date.minute());
 Serial.print(time_buf);
 return String(time_buf);
}

String ClsRelayIrrigationPrg::DateTimeToString_YYMMDD(DateTime date)
{
 char time_buf[12]; // size big enough
 sprintf(time_buf, "%04u:%02u:%02u: ", date.year(), date.month(), date.day());
 Serial.print(time_buf);
 return String(time_buf);
}

String ClsRelayIrrigationPrg::DateTimeToString_YYMMDD_HHMM(DateTime date)
{
 char time_buf[17]; // size big enough
 sprintf(time_buf, "%04u-%02u-%02u %02u:%02u ", date.year(), date.month(), date.day(), date.hour(), date.minute());
 Serial.print(time_buf);
 return String(time_buf);
}