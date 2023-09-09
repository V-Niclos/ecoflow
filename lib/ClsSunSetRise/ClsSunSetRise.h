
#ifndef CLSSUNSETRISE_H
#define CLSSUNSETRISE_H
#include <Arduino.h>
#include <time.h>
#include <sunset.h>
class ClsSunSetRise
{
private:
    //	Cabanillas de la Sierra, Madrid, Spain
    // Latitud: 40.8197, Longitud: -3.62607
    double m_latitude = 40.8197;
    double m_longitude = -3.62607;
    int m_timeZoneHH = 1;
    int m_timeZoneDayLight = 1;
    int m_Dst_Offseet = 1;
    int m_dts_dayLight = 1;

    // put function declarations here:
    SunSet m_SunSetRise;

     String fncFormatHHMM(int value);

public:
    ClsSunSetRise(/* args */);
    ~ClsSunSetRise();
    void setup(double latitude, double longitude, int timeZoneHH, int timeZoneDayLight);
    String getSunsetHHMM(uint16_t year, u_int8_t month, u_int8_t day);
    String getSunriseHHMM(uint16_t year, u_int8_t month, u_int8_t day);
};
#endif