#include "ClsRelayIrrigationPrg.h"
extern RemoteDebug Debug;

ClsRelayIrrigationPrg::ClsRelayIrrigationPrg(/* args */)
{
}
ClsRelayIrrigationPrg::~ClsRelayIrrigationPrg()
{
}
void ClsRelayIrrigationPrg::setup(uint8_t relayId, uint relayPin, String relayName, bool bResetFactoryRelays)
{
    debugI("ClsRelayIrrigationPrg  setting id %u, pin %u  name %s bResetFactoryRelays=%u", relayId, relayPin, relayName.c_str(), bResetFactoryRelays);
    m_PrgAuto_Start_Counter = 0;
    m_RelayId = relayId;
    m_RelayConfigFile = "/irrigation" + String(m_RelayId) + ".json";
    m_RelayPin = relayPin;
    m_RelayName = relayName;
    m_PrgAuto_IsActive = false;
    pinMode(m_RelayPin, OUTPUT);
    digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
    debugI("ClsRelayIrrigationPrg setted id %u, pin %u  name %s bResetFactoryRelays=%u", m_RelayId, m_RelayPin, relayName.c_str(), bResetFactoryRelays);
    if (bResetFactoryRelays)
    {
        setupPrg_ResetFactory();
        m_RelayId = relayId;
        m_RelayPin = relayPin;
        m_RelayName = relayName;
        m_PrgAuto_IsActive = false;
        String sJson = "";
        sJson = getJsonFromValues();

        fncRelayConfigSave(sJson);
    }
    fncRelayConfigRead();
    debugI("ClsRelayIrrigationPrg set read id %u, pin %u  name %s bResetFactoryRelays=%u", m_RelayId, m_RelayPin, relayName.c_str(), bResetFactoryRelays);
}
bool ClsRelayIrrigationPrg::fncCalculateIsInRange(String from, bool isActive, DateTime dt_now, DateTime dt_start, DateTime dt_stop)
{
    debugI("fncCalculateIsInRange From %s is Active %u", from.c_str(), isActive);
    if (isActive == false)
    {
        return false;
    }
    bool bDebug = true;
    bool bInStart = false;
    bool bInStop = false;
    bool bInrange = false;

    String sResult = "";
    uint32_t seconds_mow = dt_now.secondstime();
    uint32_t seconds_start = dt_start.secondstime() - 1;
    uint32_t seconds_stop = dt_stop.secondstime() + 1;
    String s_seconds_now = String(seconds_mow - 3926700000);
    String s_seconds_start = String(seconds_start - 3926700000);
    String s_seconds_stop = String(seconds_stop - 3926700000);
    String s_dt_now = DateTimeToString_YYMMDD_HHMMSS(dt_now);
    String s_dt_start = DateTimeToString_YYMMDD_HHMMSS(dt_start);
    String s_dt_stop = DateTimeToString_YYMMDD_HHMMSS(dt_stop);

    if (seconds_start < seconds_mow)
    {
        //  debugI("if (seconds_start < seconds_mow)");
        bInStart = true;
    }
    if (seconds_stop > seconds_mow)
    {
        // debugI("if (seconds_stop > seconds_mow)");
        bInStop = true;
    }
    // debugI(" bInStart=%u && bInStop=%u",bInStart, bInStop);
    bInrange = false;
    if (bInStart && bInStop)
    {
        // debugI(" if (bInStart && bInStop)");
        bInrange = true;
    }
    if (bDebug)
    {

        debugI(":::::::::::::: fncCalculateIsInRange START");

        debugI("from", from);
        debugI("m_RelayId %u", m_RelayId);
        debugI("m_PrgAuto_IsActive %s", String(m_PrgAuto_IsActive).c_str());
        debugI("m_PrgManual_IsActive %s", String(m_PrgManual_IsActive).c_str());
        debugI("s_dt_now %s", s_dt_now.c_str());
        debugI("s_dt_start %s", s_dt_start.c_str());
        debugI("s_dt_stop %s", s_dt_stop.c_str());
        debugI("bInrange %s", String(bInrange).c_str());
        debugI(":::::::::::::: fncCalculateIsInRange  END");
    }

    return bInrange;
}
bool ClsRelayIrrigationPrg::fncCalculate_Auto(DateTime dt_now)
{
    DateTime dt_Start;
    DateTime dt_Stop;
    if (m_PrgManual_IsActive)
    {
        debugI(" auto ignored becouse manual is active minutes %u", m_PrgManual_Minutes);
        return false;
    }
    if (m_PrgAuto_Minutes == 0 || m_PrgAuto_IntervalDays == 0 || m_PrgAuto_IsActive == false) // PREVENCION DE ERRORES
    {
        m_PrgAuto_IsActive == false;
        m_PrgAuto_IsDriping = false;
        digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
        return false;
    }

    if (m_PrgAuto_IsDriping == false) // if m_PrgManual_IsActive==true and not started
    {
        m_PrgAuto_Start_iHH = fncSplitString(m_PrgAuto_StartHHMM, ':', 0).toInt();
        m_PrgAuto_Start_iMM = fncSplitString(m_PrgAuto_StartHHMM, ':', 1).toInt();
        debugI("---------------m_PrgAuto_StartHHMM=%s m_PrgAuto_Start_iHH=%u  m_PrgAuto_Start_iMM=%u ", m_PrgAuto_StartHHMM, m_PrgAuto_Start_iHH, m_PrgAuto_Start_iMM);
        // si es la primera vez o se ha prgramado de nuevo las fechas de nuevo
        // las fechas se recalcula en funcion de ahora
        if (m_PrgAuto_Start_Counter == 0)
        {

            // calcualte datetime in funciton of now, m_PrgAuto_IntervalDays and m_PrgAuto_Minutes

            dt_Start = DateTime(dt_now.year(), dt_now.month(), dt_now.day(), m_PrgAuto_Start_iHH, m_PrgAuto_Start_iMM, 0);
            dt_Stop = dt_Start + TimeSpan(0, 0, m_PrgAuto_Minutes, 0);
            uint32_t seconds_now = dt_now.secondstime();
            uint32_t seconds_Start = dt_Start.secondstime();

            if (seconds_Start > seconds_now) //  dia sisguiente
            {

                dt_Start = dt_Start + TimeSpan(1, 0, 0, 0); // La primera vezComo ya ha pasado la hora el primero sera el dia siguiente.
                dt_Stop = dt_Start + TimeSpan(0, 0, m_PrgAuto_Minutes, 0);
            }
        }
        // si ya se ha regado alguna vez las fechas se calculan a partir del ultimo riego automatico
        if (m_PrgAuto_Start_Counter != 0)
        {
            debugI("AUTO Calculo siguientes dias en funcion del intervalo ");
            dt_Start = m_prgAuto_Start_LastDT + TimeSpan(m_PrgAuto_IntervalDays, 0, 0, 0); // se agregan los dias de intervalo
            dt_Stop = dt_Start + TimeSpan(0, 0, m_PrgAuto_Minutes, 0);                     // se agregan los minutos de intervalo
        }
        // se guardan los datetime calculados

        m_Calculate_Start_DT = dt_Start;
        m_Calculate_Stop_DT = dt_Stop;

        // CALCULADAS LAS FECHAS DECIDIR SI REGAR O NO
        if (fncCalculateIsInRange("AUTO START calculate need start", m_PrgAuto_IsActive, dt_now, m_Calculate_Start_DT, m_Calculate_Stop_DT))
        {
            debugI("AUTO STARTED NOW");
            m_PrgAuto_IsDriping = true;
            m_Calculate_IsInDriping = true;
            m_Calculate_IsInRange = true;
            digitalWrite(m_RelayPin, eOPENCLOSE_OPEN);
        }
    }
    if ((m_PrgAuto_IsDriping == true))
    {
        if (!fncCalculateIsInRange("AUTO START calculate need stop ", m_PrgAuto_IsActive, dt_now, m_Calculate_Start_DT, m_Calculate_Stop_DT))
        {

            m_prgAuto_Start_LastDT = m_Calculate_Start_DT;
            m_PrgAuto_Start_Counter++; // se incrementa el contador de riegos
            m_PrgAuto_IsDriping = false;

            m_Calculate_IsInDriping = false;
            m_Calculate_IsInRange = false;
            digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
        }
    }
    if (m_PrgAuto_IsDripingBefore != m_PrgAuto_IsDriping)
    {
        m_PrgAuto_IsDripingBefore = m_PrgAuto_IsDriping;

        debugI("---------- AUTO relay id %u start", m_RelayId);
        if (m_RelayId == 0)
        {
            if (m_PrgAuto_IsDriping)
            {
                debugI("STARTED NOW");
            }
            else
            {
                debugI("STOPED NOW");
            }
            debugI("m_PrgAuto_Start_Counter= %u", m_PrgAuto_Start_Counter);
            debugI("m_PrgAuto_IsDriping= %s", String(m_PrgAuto_IsDriping));
            debugI("dt_Now String= %s", DateTimeToString_YYMMDD_HHMMSS(dt_now).c_str());
            debugI("m_Calculate_Start_DT= %s", DateTimeToString_YYMMDD_HHMMSS(m_Calculate_Start_DT).c_str());
            debugI("m_Calculate_Stop_DT= %s", DateTimeToString_YYMMDD_HHMMSS(m_Calculate_Stop_DT).c_str());
            debugI("---------- relay id %u end", m_RelayId);
        }
    }
    return m_PrgAuto_IsDriping;
}

bool ClsRelayIrrigationPrg::fncCalculate_Manual(DateTime dt_now)
{
    if (m_PrgManual_IsActive == false)
    {
        debugI("------------ ClsRelayIrrigationPrg::fncCalculate_Manual m_PrgManual_IsActive==false");
        m_PrgManual_IsDriping == false; // only arrive if  m_PrgManual_IsActive= true
        return false;
    }

    if (m_PrgManual_IsDriping == false) // calculate times
    {
        debugI("------------ ClsRelayIrrigationPrg::fncCalculate_Manual  m_PrgManual_IsDriping == false");
        m_Calculate_Start_DT = dt_now + TimeSpan(0, 0, 0, 0); // dd hh mm ss
        m_Calculate_Stop_DT = m_Calculate_Start_DT + TimeSpan(0, 0, m_PrgManual_Minutes, 0);

        // only activate if is in range
        if (fncCalculateIsInRange("NANUAL START", m_PrgManual_IsActive, dt_now, m_Calculate_Start_DT, m_Calculate_Stop_DT))
        {
            m_PrgManual_IsDriping = true;
            m_Calculate_IsInDriping = true;
            m_Calculate_IsInRange = true;
            digitalWrite(m_RelayPin, eOPENCLOSE_OPEN);
        }
    }
    if (m_PrgManual_IsDriping == true)
    {
        if (!fncCalculateIsInRange("MANUAL STOP", m_PrgManual_IsActive, dt_now, m_Calculate_Start_DT, m_Calculate_Stop_DT))
        {
            m_PrgManual_IsActive = false;
            m_PrgManual_IsDriping = false;
            m_Calculate_IsInRange = false;
            m_Calculate_IsInDriping = false;
            digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
        }
    }
    if (m_PrgManual_IsDripingBefore != m_PrgManual_IsDriping)
    {
        m_PrgManual_IsDripingBefore = m_PrgManual_IsDriping;
        debugI("---------- MANUAL relay id %u start", m_RelayId);
        if (m_RelayId == 0)
        {
            if (m_PrgManual_IsDriping)
            {
                debugI("STOPED NOW");
            }
            else
            {
                debugI("STARTED NOW");
            }

            debugI("m_PrgManual_IsDriping= %s", String(m_PrgManual_IsDriping));
            debugI("dt_Now_String= %s", DateTimeToString_YYMMDD_HHMMSS(dt_now).c_str());
            debugI("m_Calculate_Start_DT= %s", DateTimeToString_YYMMDD_HHMMSS(m_Calculate_Start_DT).c_str());
            debugI("m_Calculate_Stop_DT= %s", DateTimeToString_YYMMDD_HHMMSS(m_Calculate_Stop_DT).c_str());
            debugI("---------- relay id %u end", m_RelayId);
        }
    }
    return m_PrgManual_IsDriping;
}
void ClsRelayIrrigationPrg::loop(DateTime now, bool forceResetFactory, bool bWithoutWaiting)
{

    uint32_t seconds_now = now.secondstime();
    uint32_t dif = 0;
    if (!bWithoutWaiting) // do inmediatly, do  not wait in loop
    {
        if (forceResetFactory)
        {
            setupPrg_ResetFactory(); // programation reset to factory default values
            return;
        }
        // evitar calculo y movimeinto de reles continuo

        if (seconds_now < m_loopIntervalSecodtimePrevious)
        {
            m_loopIntervalSecodtimePrevious = seconds_now;
            return;
        }
        dif = seconds_now - m_loopIntervalSecodtimePrevious;
        if (dif < m_loopIntervalSecodtime)
        {
            return;
        }
        debugI("ClsRelayIrrigationPrg::loop Relay= %u  m_loopIntervalSecodtimePrevious=%d  dif=%d", m_RelayId, m_loopIntervalSecodtimePrevious, dif);

        m_loopIntervalSecodtimePrevious = seconds_now;
    }
    debugI(" ClsRelayIrrigationPrg::loop manual call fncCalculate_Manual ");
    bool b = false;
    b = fncCalculate_Manual(now);

    if (!b)
    {
        debugI(" ClsRelayIrrigationPrg::loop manual call fncCalculate_Auto ");
        b = fncCalculate_Auto(now);
    }

    // TODO verificar error crash con rtclib

    return;
}

//=================================================================================0
//=================================================================================0
//=================================================================================0
void ClsRelayIrrigationPrg::setupPrg_Auto(String prgAuto_Description, bool prgAuto_IsActive, String PrgAuto_StartHHMM, uint8_t prgAuto_Minutes, uint8_t prgAuto_IntervalDays)
{
    if (prgAuto_Minutes > 15)
    {
        prgAuto_Minutes = 15;
    }
    m_PrgAuto_Description = prgAuto_Description;
    if (PrgAuto_StartHHMM == "")
    {
        PrgAuto_StartHHMM = "00:00";
    }
    m_PrgAuto_StartHHMM = PrgAuto_StartHHMM;
    m_PrgAuto_Start_iHH = fncSplitString(m_PrgAuto_StartHHMM, ':', 0).toInt();
    m_PrgAuto_Start_iMM = fncSplitString(m_PrgAuto_StartHHMM, ':', 1).toInt();
    m_PrgAuto_Start_Counter = 0;
    m_PrgAuto_IsActive = prgAuto_IsActive;
    m_PrgAuto_Start_Counter = 0;

    m_PrgAuto_Minutes = prgAuto_Minutes;
    m_PrgAuto_IntervalDays = prgAuto_IntervalDays;
    m_RelayMessage = "No message";
    // fncCalculateIrrigation(prgId);
}

/// @brief
/// @param prgManual_now
/// @param prgManualMinutes
void ClsRelayIrrigationPrg::setupPrg_Manual(DateTime prgManual_now, uint8_t prgManualMinutes)
{

    if (prgManualMinutes > 15)
    {
        prgManualMinutes = 15;
    }
    debugI("setupPrg_Manual 1 minutes=%u IsActive=%u  m_PrgManual_IsDriping=%u", prgManualMinutes, m_PrgManual_IsActive, m_PrgManual_IsDriping);
    if (prgManualMinutes == 0)
    {

        m_PrgManual_IsActive = false;
        m_PrgManual_IsDriping = false;
        digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
        debugI("Manual closed minutes = 0");
    }
    else
    {

        m_PrgManual_IsActive = true;
        m_PrgManual_StartHHMM = DateTimeToString_HHMM(prgManual_now);
        m_PrgManual_Minutes = prgManualMinutes;
        m_PrgManual_Description = "Prg manual minutes=" + String(prgManualMinutes);
    }
    debugI("setupPrg_Manual 2 minutes=%u IsActive=%u  m_PrgManual_IsDriping=%u", prgManualMinutes, m_PrgManual_IsActive, m_PrgManual_IsDriping);
    loop(prgManual_now, false, true);
}

uint8_t ClsRelayIrrigationPrg::getRelayIsOpen()
{
    if (digitalRead(m_RelayPin) == eOPENCLOSE_OPEN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
uint8_t ClsRelayIrrigationPrg::getPin() { return m_RelayPin; }
String ClsRelayIrrigationPrg::getJsonFromValues()
{
    String result = "{";
    result += "\"m_RelayId\":\"" + String(m_RelayId) + "\", ";
    result += "\"m_RelayName\":\"" + m_RelayName + "\", ";
    result += "\"m_PrgAuto_Description\":\"" + m_PrgAuto_Description + "\", ";
    result += "\"m_PrgAuto_Minutes\":\"" + String(m_PrgAuto_Minutes) + "\", ";
    result += "\"m_PrgAuto_IntervalDays\":\"" + String(m_PrgAuto_IntervalDays) + "\", "; // Don't need, buy is good for fill html
    result += "\"m_PrgAuto_IsActive\":\"" + String(m_PrgAuto_IsActive) + "\", ";
    result += "\"m_PrgAuto_StartHHMM\":\"" + m_PrgAuto_StartHHMM + "\", ";
    result += "\"m_RelayMessage\":\"" + m_RelayMessage + "\"";
    result += "}";
    debugI("getGson form values= %s", result.c_str());
    return result;
}
void ClsRelayIrrigationPrg::setupPrg_ResetFactory()
{

    DateTime m_time0 = time(0);

    m_RelayName = "";
    m_RelayMessage = ""; // last message filled in loop, like "Error...., OK, starte by manual option ..."
    calculate_DT_Last_Driping = time(0);
    m_Litres_today = 0;

    // ma_Litres_month[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // ma_litres_day[31] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    m_PrgAuto_Description = "";
    m_PrgAuto_IsActive = false;
    m_PrgAuto_StartHHMM = "00:00";
    m_PrgAuto_Start_iHH = 0;
    m_PrgAuto_Start_iMM = 0;
    m_PrgAuto_Minutes = 0;
    m_PrgAuto_IntervalDays = 0; // 0=nunca, 1=cada dia, 2=dias alternos

    m_PrgManual_Description = "";
    m_PrgManual_IsActive = false;
    m_PrgManual_StartHHMM = "00:00";
    m_PrgManual_Minutes = 0;

    m_Calculate_Start_DT = m_time0;
    m_Calculate_Stop_DT = m_time0;
    m_Calculate_IsInRange = false;
    m_Calculate_IsInDriping = false;
}
bool ClsRelayIrrigationPrg::setJsonToValues(String jsonConfig)
{
    // //debugI(" ClsRelayIrrigationPrg::setJsonToValues =");
    ////debugI("%s", jsonConfig.c_str());
    // //debugI("ClsRelayIrrigationPrg::setJson jsonConfig=%s", jsonConfig.c_str());
    // Serial.println(jsonConfig);
    DeserializationError error = deserializeJson(m_JsonDoc, jsonConfig.c_str());
    if (error)
    {
        debugI("deserializeJson() failed: %s "), error.f_str();

        return false;
    }
    debugI("setJsonToValues %s", jsonConfig.c_str());
    JsonObject jsObject = m_JsonDoc.as<JsonObject>();

    m_RelayId = m_JsonDoc["m_RelayId"].as<uint8_t>();
    m_RelayName = m_JsonDoc["m_RelayName"].as<String>();
    m_RelayMessage = m_JsonDoc["m_RelayMessage"].as<String>();
    if (m_RelayMessage = "null")
    {
        m_RelayMessage = "";
    }
    m_PrgAuto_Description = m_JsonDoc["m_PrgAuto_Description"].as<String>();
    m_PrgAuto_IsActive = m_JsonDoc["m_PrgAuto_IsActive"].as<bool>();
    m_PrgAuto_StartHHMM = m_JsonDoc["m_PrgAuto_StartHHMM"].as<String>();

    m_PrgAuto_Minutes = m_JsonDoc["m_PrgAuto_Minutes"].as<uint8_t>();
    String s = "";
    m_PrgAuto_IntervalDays = m_JsonDoc["m_PrgAuto_IntervalDays"].as<uint8_t>();
    return true;
}

String ClsRelayIrrigationPrg::fncSplitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
bool ClsRelayIrrigationPrg::fncRelayConfigSave(String jsonConfig)
{

    //  debugI("SAVE: Json file = %s, value= %s",m_RelayConfigFile.c_str(), jsonConfig.c_str());
    return ClsFileSpiffs::fileWrite(m_RelayConfigFile, jsonConfig);
}

void ClsRelayIrrigationPrg::fncRelayConfigRead()
{

    Serial.println("ClsRelayIrrigationPrg::fncRelayConfigRead" + m_RelayConfigFile);
    if (!ClsFileSpiffs::fileExist(m_RelayConfigFile))
    {
        setupPrg_ResetFactory();
    }
    String jsonConfig = ClsFileSpiffs::fileRead(m_RelayConfigFile);
    debugI("READ: Json file = %s, value= %s", m_RelayConfigFile.c_str(), jsonConfig.c_str());
    setJsonToValues(jsonConfig);
}

String ClsRelayIrrigationPrg::getHtmlStatus()
{

    String result = "<fieldset>";
    result += " <legend><b>Irrigation. RelayId = " + String(m_RelayId) + " RelayName = " + m_RelayName + "</b>";

    if (getRelayIsOpen())
    {
        result.concat("<span class=\"led green\"></span>");
    }
    else
    {
        result.concat("<span class=\"led red\"></span>");
    }

    // result += "</legend><p>";
    result.concat("</legend>");
    result.concat("<ul><li><b>Programation  Auto</b>");
    result.concat("<li>Active=" + String(m_PrgAuto_IsActive));
    result.concat("</li><li> Description= " + m_PrgAuto_Description);
    result.concat("</li><li> Start= " + fncHHMM_EmptyBadValue(m_PrgAuto_StartHHMM));
    result.concat("</li><li> Minutes= " + String(m_PrgAuto_Minutes));
    result.concat("</li><li> Interval days= " + String(m_PrgAuto_IntervalDays));
    if (m_PrgAuto_IsActive)
    {
        result.concat("</li><li>Next irrigation " + DateTimeToString_YYMMDD_HHMM(m_Calculate_Start_DT));
    }
    result.concat("</li></ul>");
    if (m_PrgManual_IsDriping)
    {
        result.concat("<ul><li><b>Programation  Manual active</b>");
        result.concat("</li><li> Start= " + fncHHMM_EmptyBadValue(m_PrgManual_StartHHMM));
        result.concat("</li><li> Minutes= " + String(m_PrgManual_Minutes));
        result.concat("</li><li> Stop At= " + String(DateTimeToString_YYMMDD_HHMM(m_Calculate_Stop_DT)));
        result.concat("</li></ul>");
    }
    if (m_PrgAuto_Start_Counter > 0)
    {
        result.concat("<br/>Last irrigation" + DateTimeToString_YYMMDD_HHMM(m_prgAuto_Start_LastDT));
    }

    result.concat("</p> </fieldset>");
    return result;
}
String ClsRelayIrrigationPrg::fncHHMM_EmptyBadValue(String HHMM)
{
    if (HHMM == "null")
    {
        HHMM = "";
    }
    if (HHMM == "99:99")
    {
        HHMM = "";
    }
    return HHMM;
}
String ClsRelayIrrigationPrg::DateTimeToString_HHMM(DateTime date)
{
    char FORMAT[] = "hh:mm";
    return String(date.toString(FORMAT));
}

String ClsRelayIrrigationPrg::DateTimeToString_YYMMDD(DateTime date)
{
     char FORMAT[] = "YYYY-MM-DD";
    return String(date.toString(FORMAT));
}

String ClsRelayIrrigationPrg::DateTimeToString_YYMMDD_HHMM(DateTime date)
{
    char FORMAT[] = "YYYY-MM-DD hh:mm";
    return String(date.toString(FORMAT));
}
String ClsRelayIrrigationPrg::DateTimeToString_YYMMDD_HHMMSS(DateTime date)
{
      char FORMAT[] = "YYYY-MM-DD hh:mm:ss";
    return String(date.toString(FORMAT));
}

void ClsRelayIrrigationPrg::debug(String sFrom)
{

    String s = "";
    debugI(" ========== ClsRelayIrrigationPrg,debug from %s", sFrom.c_str());
    debugI(" m_RelayId = %u", m_RelayId);
    debugI(" m_RelayName = %s", m_RelayName.c_str());
    debugI(" m_RelayPin = %u", m_RelayPin);
    debugI("m_RelayMessage %s", m_RelayMessage.c_str());
    debugI("...");

    debugI("AUTO");
    s = String(m_PrgAuto_IsActive);
    debugI(" m_PrgAuto_IsActive = %s", s);
    debugI(" m_PrgAuto_Description = %s", m_PrgAuto_Description.c_str());
    debugI(" m_PrgAuto_IntervalDays = %u", m_PrgAuto_IntervalDays);
    debugI(" m_PrgAuto_Start_iHH = %u", m_PrgAuto_Start_iHH);
    debugI(" m_PrgAuto_Minutes = %u", m_PrgAuto_Minutes);

    debugI("MANUAL");
    s = String(m_PrgManual_IsActive);
    debugI("m_PrgManual_IsActive= %s", s);
    debugI("m_PrgManual_Description= %S", m_PrgManual_Description.c_str());
    debugI("m_PrgManual_Minutes= %u", m_PrgManual_Minutes);
    debugI("m_PrgManual_StartHHMM= %s", m_PrgManual_StartHHMM.c_str());
    s = String(m_PrgManual_IsDriping);
    debugI("m_PrgManual_IsDriping= %s", s.c_str());

    debugI("CALCULATE");

    debugI(" m_Calculate_Start_STR = %s", DateTimeToString_YYMMDD_HHMM(m_Calculate_Start_DT).c_str());
    debugI(" m_Calculate_Stop_STR = %s", DateTimeToString_YYMMDD_HHMM(m_Calculate_Stop_DT).c_str());

    s = String(m_Calculate_IsInRange);
    debugI("m_Calculate_IsInRange %s", s.c_str());
    s = String(m_Calculate_IsInDriping);
    debugI("m_Calculate_IsInDriping %s", s.c_str());

    debugI("=======================================");
}
String ClsRelayIrrigationPrg::get_RelayMessage() { return m_RelayMessage; }