#include "ClsTimeRtcNtp.h"

extern RemoteDebug Debug;
ClsTimeRtcNtp::ClsTimeRtcNtp(/* args */)
{
}
ClsTimeRtcNtp::~ClsTimeRtcNtp()
{
}

void ClsTimeRtcNtp::setup()
{

    setup(m_NtpServer_default, m_NtpTimeZone_default, m_NtpTimeZone_DayLight_default, m_GpsLatitudeDefault, m_GpsLongitudeDefault);
    begin();
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
        if (m_Debug)
        {
            debugE("RTC lost power, setting a base datetime");
            m_Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
            m_NowLastRead = m_Rtc.now();
        }
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
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

    // todo estos datos estan sobreescrito a capon de madrid
    // 40.4165, -3.70256
    m_NtpTimeZone = 1;
    m_NtpTimeZoneDayLight = 1;
    m_GpsLatitude = 40.4165;
    m_GpsLongitude = -3.70256;
    SunSetRise.setup_Location(m_GpsLatitude, m_GpsLongitude, m_NtpTimeZone, m_NtpTimeZoneDayLight);

    configTime(m_NtpLocalGmtOffset_sec, m_NtpLocalDaylightOffset_sec, ntpServer.c_str());
    fncReadNowNTP();
}

void ClsTimeRtcNtp::fncFillDateTimevalues()
{

    m_NowLastRead = m_Rtc.now();
    m_RtcIntervalPrevious = millis();
    m_TimelLocalYear = m_NowLastRead.year();
    m_TimelLocalMonth = m_NowLastRead.month();
    m_TimelLocalDayMonth = m_NowLastRead.day();
    m_TimelLocalDayWeek = m_NowLastRead.dayOfTheWeek();

    m_TimelLocalHour = m_NowLastRead.hour();
    m_TimelLocalMin = m_NowLastRead.minute();
    m_TimelLocalSec = m_NowLastRead.second();
    m_TimeLocal_MinuteOfDay = m_TimelLocalHour * 60 + m_TimelLocalMin;
    m_DateLocalYYYYMMDD_HHMMSS = DateTimeToString_YYYYMMDD_HHMMSS(m_NowLastRead);
    m_DateLocalYYYYMMDD = fncFormatYYYYMMDD(m_TimelLocalYear, m_TimelLocalMonth, m_TimelLocalDayMonth);
    m_TimeLocalHHMM = fncFormatHHMMSS(m_TimelLocalHour, m_TimelLocalMin, m_TimelLocalMin);
    SunSetRise.loop(m_NowLastRead);
}

void ClsTimeRtcNtp::loop(bool bDebug)
{
    m_Debug = bDebug;
    uint32_t dif = 0;
    uint32_t ulMillis = millis();
    // update rtc from ntp
    if (m_NtpIntervalPrevious > ulMillis)
    {
        m_NtpIntervalPrevious = 0;
    }
    dif = ulMillis - m_NtpIntervalPrevious;
    if (dif > m_NtpIntervalSwitch)
    {

        fncReadNowNTP();
        debugI("m_NtpIntervalSwitch=%d  dif=%d", m_RtcIntervalSwitch, dif);
        debugI("update ntp time %s", m_DateLocalYYYYMMDD_HHMMSS.c_str());
        m_NtpIntervalPrevious = ulMillis;
    }

    if (m_RtcIntervalPrevious > ulMillis)
    {
        m_RtcIntervalPrevious = 0;
    }
    dif = ulMillis - m_RtcIntervalPrevious;
    if (dif > m_RtcIntervalSwitch)
    {
        fncFillDateTimevalues();
        // debugI("RTC read %s", m_DateLocalYYYYMMDD_HHMMSS.c_str());
        m_RtcIntervalPrevious = ulMillis;
    }
}

void ClsTimeRtcNtp::fncReadNowNTP()
{
    debugI("---------------------- get nps set rtc");
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

    char buf64[64];
    sprintf(buf64, "%02d/%02d/%02d %02d:%02d:%02d", m_Time_Local.tm_year + 1900, m_Time_Local.tm_mon + 1, m_Time_Local.tm_mday, m_Time_Local.tm_hour, m_Time_Local.tm_min, m_Time_Local.tm_sec);

    debugI("NTP  Antes de crear dt  datetime local = %s", buf64);
    DateTime dt = DateTime(m_Time_Local.tm_year, m_Time_Local.tm_mon + 1, m_Time_Local.tm_mday, m_Time_Local.tm_hour, m_Time_Local.tm_min, m_Time_Local.tm_sec);
    // debugI("despues de crear datetime ");
    m_Rtc.adjust(dt); // Set Day-of-W
    
    DateTime rtcNow = m_Rtc.now();
    char buf_YYMMDD_HHMMSS[] = "YYYY-MM-DD hh:mm:ss";
    String sDatetime = rtcNow.toString(buf_YYMMDD_HHMMSS);
 debugI("RTC Actualizado a %s",rtcNow.toString(buf_YYMMDD_HHMMSS));
    debugI("rtc ajuct to %s", sDatetime.c_str());
    m_NtpReaded = true;
    m_NtpIntervalPrevious = millis();

    fncFillDateTimevalues();
    // debugI(" hasta aqui bien fncReadNowNTP despues de fncFillDateTimevalues el reloj");
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
  String DateTimeToString_YYYYMMDD_HHMM(DateTime dt)
  {
     String s;
    char buf2[] = "YYYY-MM-DD  hh:mm";
    s = dt.toString(buf2);
    return s;
  }
String ClsTimeRtcNtp::DateTimeToString_YYYYMMDD_HHMMSS(DateTime dt)
{
    String s;
    char buf2[] = "YYYY-MM-DD  hh:mm:ss";
    s = dt.toString(buf2);
    return s;
}
String ClsTimeRtcNtp::TimeLocalHHMM() { return m_TimeLocalHHMM; }

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
    fncFillDateTimevalues();
    DateTime t_next = m_NowLastRead + TimeSpan(addDays, 0, 0, 0);

    return t_next;
}

DateTime ClsTimeRtcNtp::nowDateTime_lastRead()
{

    // fncFillDateTimevalues();
    return m_NowLastRead;
}

String ClsTimeRtcNtp::NowString()
{

    return DateTimeToString_YYYYMMDD_HHMMSS(m_Rtc.now());
}
