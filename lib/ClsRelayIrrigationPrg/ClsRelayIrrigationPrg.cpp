#include "ClsRelayIrrigationPrg.h"
#include "time.h"
ClsRelayIrrigationPrg::ClsRelayIrrigationPrg(/* args */)
{
}
ClsRelayIrrigationPrg::~ClsRelayIrrigationPrg()
{
}
void ClsRelayIrrigationPrg::setup(uint8_t relayId, uint relayPin, String relayName,bool forceReset)
{
    m_RelayId = relayId;
    m_RelayPin = relayPin;
    m_RelayName = relayName;
    m_RelayConfigFile = "/irrigation" + String(relayId) + ".json";
    pinMode(m_RelayPin, OUTPUT);
    digitalWrite(m_RelayPin, eIrrigation_CLOSE);
    if (forceReset) {fncRelayConfigResetDefault();}

    debugV("ClsRelayIrrigationPrg::setup m_RelayId=%d m_RelayName=%s m_RelayConfigFile=%s",
        m_RelayId, m_RelayName.c_str(), m_RelayConfigFile.c_str());
    fncRelayConfigRead();
}
void ClsRelayIrrigationPrg::loop()
{
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

    for (uint8_t id = 0; id < m_IrrigationPrograms; id++)
    {

        // todo develop logical process
        if (ma_PrgOnOff[id] == eOnOff_OFF)
        {
            digitalWrite(m_RelayPin, eIrrigation_CLOSE);
        }
        else
        {

            // todo develop logical process
            if (ma_PrgMode[id] == ePrgModeMANUAL)
            {
                // TODO
            }
            // todo develop logical process
            if (ma_PrgMode[id] == ePrgModeAUTO)
            {
                // TODO
            }
        }
    }
    // maybe not well configured, the  close
    digitalWrite(m_RelayPin, eIrrigation_CLOSE);
}

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
    fncCalculateIrrigation(prgId);
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
    fncCalculateIrrigation(prgId);
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
    fncCalculateIrrigation(prgId);
}
void ClsRelayIrrigationPrg::fncRelayConfigResetDefault()
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
    ma_PrgStartTime[i] = 0;
    ma_PrgStopTime[i] = 0;
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
    ma_PrgStartTime[i] = 0;
    ma_PrgStopTime[i] = 0;
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
    ma_PrgStartTime[i] = 0;
    ma_PrgStopTime[i] = 0;
}

uint8_t ClsRelayIrrigationPrg::getRelayIsOpen()
{
    if (digitalRead(m_RelayPin) == eIrrigation_OPEN)
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
    /*
       {
           "relayIrrigation":
       [
       {"relayName": "Irrigation 2", "relayId": "1"}
       ],
         "prg":
         [
           {	"id": "0", "name": "prg 0", "mode": "1", "onOff": "0", "startHHMM": "12:35", "minutes": "6", "intervalDays": "2"},
           {	"id": "1", "name": "prg 1", "mode": "1", "onOff": "0", "startHHMM": "14:35", "minutes": "5", "intervalDays": "3"},
           { "id": "2", "name": "prg 2", "mode": "2", "onOff": "0", "startHHMM": "16:01", "minutes": "16", "intervalDays": "3"}]}
       */

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
    return result;
}

bool ClsRelayIrrigationPrg::setJson(String jsonConfig)
{
    /*
    {
        "relayIrrigation":
    [
    {"relayName": "Irrigation 2", "relayId": "1"}
    ],
      "prg":
      [
        {	"id": "0", "name": "prg 0", "mode": "1", "onOff": "0", "startHHMM": "12:35", "minutes": "6", "intervalDays": "2"},
        {	"id": "1", "name": "prg 1", "mode": "1", "onOff": "0", "startHHMM": "14:35", "minutes": "5", "intervalDays": "3"},
        { "id": "2", "name": "prg 2", "mode": "2", "onOff": "0", "startHHMM": "16:01", "minutes": "16", "intervalDays": "3"}]}
    */

    DeserializationError error = deserializeJson(m_JsonDoc, jsonConfig);

    // Test if parsing succeeds.
    if (error)
    {
        debugE("deserializeJson() failed: %s", error.c_str());
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
       return ClsFileSpiffs::fileWrite(m_RelayConfigFile, getJson());
}

void ClsRelayIrrigationPrg::fncRelayConfigRead()
{

    debugV("reading config file %s", m_RelayConfigFile);
    if (!ClsFileSpiffs::fileExist(m_RelayConfigFile))
    {
        // if not exist previous config
        // set default values and save
        setupPrg_0_DefaultAuto();
        setupPrg_1_DefaultAuto();
        setupPrg_2_DefaultManual();
        fncRelayConfigSave();
    }
    String sRead=ClsFileSpiffs::fileRead(m_RelayConfigFile);
    setJson(sRead);

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
        result += "<br/> Minutes= " +  String(ma_PrgMinutes[idPrg]);
        result += "<br/> Interval days= " +  String(ma_PrgIntervalDays[idPrg]);
        result += "<br/> Start time" + ma_PrgStartHHMM[idPrg];
        result += "<br/> Stop time" + ma_PrgStartHHMM[idPrg];
        result += "</p>";
    }
    result += "</p>";
    return result;
}
