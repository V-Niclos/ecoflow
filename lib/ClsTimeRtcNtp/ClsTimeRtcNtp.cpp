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
void ClsTimeRtcNtp::fncRtcBegin()
{
    if (!m_Rtc.begin())
    {
         Serial.println("Couldn't find RTC");
         Serial.flush();
        abort();
    }
    if (m_Rtc.lostPower())
    {
        // Serial.println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        m_Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
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
    m_Rtc.begin(); // Inicializamos el RTC
    fncReadNowNTP();
}
void ClsTimeRtcNtp::loop()
{
    // unsigned long m_Ntpcounter=0;
    // int64_t m_NtpIntervalSwitch=60000;
    // int64_t m_NtpIntervalPrevious=0;

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
        // Serial.println("Failed to obtain local time ");
        return;
    }
    configTime(0, 0, m_NtpServer.c_str());
    if (!getLocalTime(&m_time_UTC))
    {
        // // Serial.println("Failed to obtain UTC time ");
        return;
    }
    m_NtpReaded = true;
    m_NtpIntervalPrevious = m_NtpIntervalActual;
    m_Ntpcounter++;
    m_TimelLocalYear = 1900 + m_Time_Local.tm_year;
    m_TimelLocalMonth = m_Time_Local.tm_mon;
    m_TimelLocalDayMonth = m_Time_Local.tm_mday;
    m_TimelLocalDayWeek = m_Time_Local.tm_wday;
    m_TimelLocalDayYear = m_Time_Local.tm_yday;
    m_TimelLocalHour = m_Time_Local.tm_hour;
    m_TimelLocalMin = m_Time_Local.tm_min;
    m_TimelLocalSec = m_Time_Local.tm_sec;
    m_TimeLocal_MinuteOfDay = m_Time_Local.tm_hour * 60 + m_Time_Local.tm_min;

    m_DateLocalYYYYMMDD = fncFormatYYYYMMDD(m_TimelLocalYear, m_TimelLocalMonth, m_TimelLocalDayMonth);
    m_TimeLocalHHMM = fncFormatHHMMSS(m_TimelLocalHour, m_TimelLocalMin, m_TimelLocalMin);

    m_TimelUTCYear = 1900 + m_time_UTC.tm_year;
    m_TimelUTCMonth = m_time_UTC.tm_mon;
    m_TimelUTCDayMonth = m_time_UTC.tm_mday;
    m_TimelUTCDayWeek = m_time_UTC.tm_wday;
    m_TimelUTCDayYear = m_time_UTC.tm_yday;
    m_TimelUTCHour = m_time_UTC.tm_hour;
    m_TimelUTCMin = m_time_UTC.tm_min;
    m_TimelUTCSec = m_time_UTC.tm_sec;
    // fncLoopSunset(m_TimelUTCDayYear, m_TimelUTCDayMonth, m_TimelUTCMin);
    debugSerial();
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
    // struct tm timeinfo;
    // // Serial.println("========================================================");
    // Serial.print("m_Ntpcounter=");
    // Serial.print(m_Ntpcounter);
    // Serial.print(" m_NtpIntervalPrevious=");
    // Serial.print(m_NtpIntervalPrevious);
    // Serial.print(" m_NtpIntervalSwitch=");
    // Serial.println(m_NtpIntervalSwitch);
    // Serial.print(" m_NtpLocalGmtOffset_sec=");
    // Serial.print(m_NtpLocalGmtOffset_sec);
    // Serial.print(" m_NtpLocalDaylightOffset_sec=");
    // Serial.println(m_NtpLocalDaylightOffset_sec);

    // Serial.println(&m_Time_Local, "Local=%A, %B %d %Y %H:%M:%S");
    // Serial.println(&m_time_UTC, "Utc=%A, %B %d %Y %H:%M:%S");
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
    // Serial.println("now_Add_Days");
    char buf1[20];
    DateTime t_now = m_Rtc.now();
    // DateTime(year, month, day, hour, min, sec);
    // DateTime StopTimePlusTwoHoursAndThirtyMinutes = stopTime + TimeSpan(0, 2, 30, 0);
    DateTime t_next = t_now + TimeSpan(addDays, 0, 0, 0);
    sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d", t_now.hour(), t_now.minute(), t_now.second(), t_now.day(), t_now.month(), t_now.year());
    // Serial.print("Date/Time now: ");
    // Serial.println(buf1);
    sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d", t_next.hour(), t_next.minute(), t_next.second(), t_next.day(), t_next.month(), t_next.year());
    // Serial.print("Date/Time next: ");
    // Serial.println(buf1);
    return t_next;
}

DateTime ClsTimeRtcNtp::NowDateTime ()
{ return m_Rtc.now(); 
}
String ClsTimeRtcNtp::NowString()
{
    // Serial.println("now_Add_Days");
    char buf1[20];
    DateTime t_now = m_Rtc.now();
    sprintf(buf1, "%02d:%02d:%02d %02d-%02d-%02d", t_now.hour(), t_now.minute(), t_now.second(), t_now.day(), t_now.month(), t_now.year());
    // Serial.print("Date/Time now: ");
    // Serial.println(buf1);
    return String(buf1);
}