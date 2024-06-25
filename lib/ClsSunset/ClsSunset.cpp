#include "ClsSunset.h"

ClsSunset::ClsSunset(/* args */)
{
}

ClsSunset::~ClsSunset()
{
}
void ClsSunset::setup_Location(float latitude, float longitude, int dst_Offseet, int dts_dayLight)
{
    m_latitude = latitude;
    m_longitude = longitude;
    m_dst_Offseet = dst_Offseet;
    m_dts_dayLight = dts_dayLight;
}
void ClsSunset::loop(DateTime calculate_datetime)
{
   
    uint8_t today=calculate_datetime.day();
    if (today==m_calcualteLastDay){return;}
    debugI ("today =%d m_calcualteLastDay=%d",today, m_calcualteLastDay );
    m_calcualteLastDay=today;
    m_Calculate_DateTime = calculate_datetime;
    m_Calculate_YYYYMMDDD_HHMM = DateTimeToString_YYMMDD_HHMM(m_Calculate_DateTime);
    ClsDusk2Dawn lat_long(m_latitude, m_longitude, m_dst_Offseet + m_dts_dayLight);
    int m_sunrise_minute = lat_long.sunrise(m_Calculate_DateTime.year(), m_Calculate_DateTime.month(), m_Calculate_DateTime.day(), false);
    int m_sunset_minute = lat_long.sunset(m_Calculate_DateTime.year(), m_Calculate_DateTime.month(), m_Calculate_DateTime.day(), false);
    char Sunrise_time[20];
    ClsDusk2Dawn::min2str(Sunrise_time, m_sunrise_minute);
    m_sunrise_HHMM = String(Sunrise_time);
    //debugI("Sunrise: %s", Sunrise_time);
    char Sunset_time[] = "00:00";
    ClsDusk2Dawn::min2str(Sunset_time, m_sunset_minute);
    m_sunset_HHMM = String(Sunset_time);
    char solarmoon_time[] = "00:00";
    int m_solarmoon_minute = m_sunrise_minute + (m_sunset_minute - m_sunrise_minute) / 2;
    ClsDusk2Dawn::min2str(solarmoon_time, m_solarmoon_minute);
    m_SolarNoon = String(solarmoon_time);
    
}
String ClsSunset::getCalculate_YYYYMMDDD_HHMM() {   return m_Calculate_YYYYMMDDD_HHMM; }
String ClsSunset::getSunsetHHMM() { return m_sunset_HHMM; }
String ClsSunset::getSunriseHHMM() { return m_sunrise_HHMM; }
uint ClsSunset::getSunset_minute() { return m_sunset_minute; }
uint ClsSunset::getSunrise_minute() { return m_sunrise_minute; }

bool ClsSunset::getIsSunset() { return m_isSunset; }

bool ClsSunset::getIsSunrise() { return m_isSunrise; }

String ClsSunset::DoubleToString(double dValue)
{
    char buffer[12];
    dtostrf(dValue, 6, 4, buffer);
    return String(buffer);
}
String ClsSunset::DateTimeToString_YYMMDD_HHMM(DateTime date)
{
    String s;
    char buf2[] = "MM-DD-YYYY  hh:mm";
    s = date.toString(buf2);
    return s;
}
void ClsSunset::debug(String callFrom)
{
    
    debugI(" ------------------ ClsSunset::debug() START");
    debugI("Called from %s",  callFrom.c_str());
    debugI("Calculate at = %s", m_Calculate_YYYYMMDDD_HHMM.c_str());
    debugI("Lat= %s, long= %s ", DoubleToString(m_latitude), DoubleToString(m_longitude));
    debugI("m_dst_Offseet= %d, m_dts_dayLight=%d ", m_dst_Offseet, m_dts_dayLight);
    debugI("m_sunset_HHMM= %s ", m_sunset_HHMM.c_str());
    debugI("getSunriseHHMM= %s ", m_sunrise_HHMM.c_str());
    debugI("m_SolarNoon= %s", m_SolarNoon.c_str());
    debugI(" ------------------ ClsSunset::debug() END");
}