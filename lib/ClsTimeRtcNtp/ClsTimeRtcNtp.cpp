#include "ClsTimeRtcNtp.h"
#include <Arduino.h>
#include <WiFi.h>
ClsTimeRtcNtp::ClsTimeRtcNtp(/* args */)
{
}
ClsTimeRtcNtp::~ClsTimeRtcNtp()
{
}

void ClsTimeRtcNtp::setup()
{

    setup(m_NtpServer_default, m_NtpTimeZone_default, m_NtpTimeZone_DayLight_default, m_GpsLatitudeDefault, m_GpsLongitudeDefault);
}
void ClsTimeRtcNtp::begin()
{
    if (!m_Rtc.begin())
    {
        debugE("Couldn't find RTC");
        abort();
    }
    if (m_Rtc.lostPower())
    {
        debugE("RTC lost power, setting a base datetime");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        m_Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void ClsTimeRtcNtp::setup(String ntpServer, int ntpTimeZone, int ntpTimeZoneDayLight, long gpsLatitude, long gpsLongitude)
{
    m_NtpServer = ntpServer;
    m_NtpTimeZone = ntpTimeZone;
    m_NtpTimeZoneDayLight = ntpTimeZoneDayLight;
    m_GpsLatitude = gpsLatitude;
    m_GpsLongitude = gpsLongitude;

    m_NtpLocalGmtOffset_sec = m_NtpTimeZone * m_NtpTime_HH_2_SS;              //(de acuerdo al paralelo)
    m_NtpLocalDaylightOffset_sec = m_NtpTimeZoneDayLight * m_NtpTime_HH_2_SS; //(De acuedo a reaguste pais)

    configTime(m_NtpLocalGmtOffset_sec, m_NtpLocalDaylightOffset_sec, ntpServer.c_str());
}
void ClsTimeRtcNtp::fncFillDateTimevalues()
{

    debugV("Reading RTC fncFillDateTimevalues");
    m_NowLastRead = m_Rtc.now();
    IntervalPreviousRead = millis();
    m_TimelLocalYear = 1900 + m_NowLastRead.year();
    m_TimelLocalMonth = m_NowLastRead.month();
    m_TimelLocalDayMonth = m_NowLastRead.day();
    m_TimelLocalDayWeek = m_NowLastRead.dayOfTheWeek();

    m_TimelLocalHour = m_NowLastRead.hour();
    m_TimelLocalMin = m_NowLastRead.minute();
    m_TimelLocalSec = m_NowLastRead.second();
    m_TimeLocal_MinuteOfDay = m_TimelLocalHour * 60 + m_TimelLocalMin;

    m_DateLocalYYYYMMDD = fncFormatYYYYMMDD(m_TimelLocalYear, m_TimelLocalMonth, m_TimelLocalDayMonth);
    m_TimeLocalHHMM = fncFormatHHMMSS(m_TimelLocalHour, m_TimelLocalMin, m_TimelLocalMin);
}

void ClsTimeRtcNtp::loop()
{
    // debugI("ClsTimeRtcNtp::loop() start" );

    m_NtpIntervalActual = millis();
    if (m_NtpIntervalPrevious > m_NtpIntervalActual)
    {
        m_NtpIntervalPrevious = 0;
    }
    if (m_NtpIntervalActual - m_NtpIntervalPrevious < m_NtpIntervalSwitch)
    {

        return;
    }

    fncReadNowNTP();
    fncFillDateTimevalues();
}

  



void ClsTimeRtcNtp::fncReadNowNTP()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        m_NtpReaded = false;
        return;
    }
    m_NtpReaded = false;
    configTime(m_NtpLocalGmtOffset_sec, m_NtpLocalDaylightOffset_sec, m_NtpServer.c_str());
    if (!getLocalTime(&m_Time_Local))
    {
        debugE("Failed to obtain local time");
        return;
    }
  
    debugI("RTC update from ntpserver");

    char buf64[64];
    sprintf(buf64,"%02d/%02d/%02d %02d:%02d:%02d", m_Time_Local.tm_year+1900, m_Time_Local.tm_mon, m_Time_Local.tm_mday, m_Time_Local.tm_hour, m_Time_Local.tm_min, m_Time_Local.tm_sec);
    debugI("get datetime local = %s",buf64);
    debugI("RTC update from ntpserver set dt");
    DateTime dt = DateTime(m_Time_Local.tm_year+1900, m_Time_Local.tm_mon, m_Time_Local.tm_mday, m_Time_Local.tm_hour, m_Time_Local.tm_min, m_Time_Local.tm_sec);
    debugI("RTC update from ntpserver set  m_Rtc.adjust");
    m_Rtc.adjust(dt); // Set Day-of-Week to SUNDAY
    m_NtpReaded = true;
    m_NtpIntervalPrevious = m_NtpIntervalActual;
    m_Ntpcounter++;

    // fncLoopSunset(m_TimelUTCDayYear, m_TimelUTCDayMonth, m_TimelUTCMin);
}
String ClsTimeRtcNtp::fncTwoDigit(int i)
{
    String result = "";
    if (i < 10)
    {
        result = "0";
    }
    result += String(i);
    return result;
}
String ClsTimeRtcNtp::fncFormatYYYYMMDD(int iYear, int iMonth, int iDay)
{
    String result = "";
    result = iYear;
    result += "-";
    result += fncTwoDigit(iMonth);
    result += "-";
    result += fncTwoDigit(iDay);
    return result;
}
String ClsTimeRtcNtp::fncFormatHHMMSS(int iHH, int iMM, int iSS)
{
    String result = "";
    result += fncTwoDigit(iHH);
    result += ":";
    result += fncTwoDigit(iMM);
    result += ":";
    result += fncTwoDigit(iMM);

    return result;
}
String ClsTimeRtcNtp::DateLocalYYYYMMDD() { return m_DateLocalYYYYMMDD; }
String ClsTimeRtcNtp::TimeLocalHHMM() { return m_TimeLocalHHMM; }
void ClsTimeRtcNtp::debugSerial()
{
    debugD("m_Time_Local=%s", asctime(&m_Time_Local));
}
String ClsTimeRtcNtp::fncMinutesToHour(double dMinutes)
{
    int iMinutes = (int)dMinutes;
    String result = "";
    int iHH = 0;
    int iMM = int(dMinutes);
    iHH = int(dMinutes / 60);
    iMM = iMM % 60;
    if (iHH < 10)
    {
        result = "0";
    }
    result = result + String(iHH) + ":";
    if (iMM < 10)
    {
        result = result + "0";
    }
    result = result + String(iMM);
    return result;
}

DateTime ClsTimeRtcNtp::getNowAddDayDateTime(uint addDays)
{
    DateTime t_now = m_Rtc.now();
    DateTime t_next = t_now + TimeSpan(addDays, 0, 0, 0);

    return t_next;
}

DateTime ClsTimeRtcNtp::nowDateTime()
{
 
    DateTime now_LastReaded;
    if (IntervalPreviousRead > millis())
    {
        IntervalPreviousRead = 0;
    }
    if (millis() - IntervalPreviousRead > intervalLapseRead)
    {
        debugV("Reading RTC");
        now_LastReaded = m_Rtc.now();
        IntervalPreviousRead = millis();
    }
    
    return now_LastReaded;
}

String ClsTimeRtcNtp::NowString()
{
    char buf1[64];
    DateTime t_now = m_Rtc.now();
    sprintf(buf1, "%02d:%02d:%02d %02d-%02d-%02d", t_now.hour(), t_now.minute(), t_now.second(), t_now.day(), t_now.month(), t_now.year());
    return String(buf1);
}
