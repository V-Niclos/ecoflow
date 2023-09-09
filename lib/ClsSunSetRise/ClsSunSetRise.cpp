#include "ClsSunSetRise.h"
ClsSunSetRise::ClsSunSetRise(/* args */)
{
}

ClsSunSetRise::~ClsSunSetRise()
{
}
void ClsSunSetRise::setup(double latitude, double longitude, int timeZoneHH, int timeZoneDayLight)
{
    m_latitude = latitude;
    m_longitude = longitude;
    m_timeZoneHH = timeZoneHH;
    m_timeZoneDayLight = timeZoneDayLight;

}
String ClsSunSetRise::fncFormatHHMM(int value)
{
    String result="";
    int val=0;
    //hh
    val=value / 60;
    if (val<10 ){result="0";}
    result+=String(val);
    result+=":";
    //mm
    val =value % 60;
     if (val<10 ){result+="0";}
    result+=String(val);
    return result;
    }

String ClsSunSetRise::getSunsetHHMM(uint16_t year, uint8_t month, uint8_t day)
{
    String result = "NaN";
    int sunset;
    m_SunSetRise.setCurrentDate(year, month, day);
    m_SunSetRise.setPosition(m_latitude, m_longitude, double(m_Dst_Offseet + m_dts_dayLight));
    sunset = static_cast<int>(m_SunSetRise.calcSunset());
    result = fncFormatHHMM(sunset);
    return result;
}
String ClsSunSetRise::getSunriseHHMM(uint16_t year, uint8_t month, uint8_t day) 
{
String result = "NaN";
    int sunrise;
    m_SunSetRise.setCurrentDate(year, month, day);
    m_SunSetRise.setPosition(m_latitude, m_longitude, double(m_Dst_Offseet + m_dts_dayLight));
    sunrise = static_cast<int>(m_SunSetRise.calcSunrise());
    result = fncFormatHHMM(sunrise);
    return result;
}
