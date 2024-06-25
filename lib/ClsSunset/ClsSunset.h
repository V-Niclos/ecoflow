
#ifndef ClsSunset_H
#define ClsSunset_H
#include "Arduino.h"
#include <Math.h>
#include "ClsDusk2Dawn.h"
#include <RTClib.h>

#include "RemoteDebug.h"

extern RemoteDebug Debug;
class ClsSunset
{
private:
    //	Cabanillas de la Sierra, Madrid, Spain
    // Latitud: 40.8197, Longitud: -3.62607
   uint8_t m_calcualteLastDay=0;
    double m_latitude = 40.41831;
    double m_longitude =-3.70275;
    int    m_dst_Offseet = 1;
    int    m_dts_dayLight = 1;
    String m_SolarNoon=""; // mediodia solar
    String m_sunset_HHMM="";
    String m_sunrise_HHMM="";
    DateTime m_Calculate_DateTime;
    String m_Calculate_YYYYMMDDD_HHMM="";

    int m_solarmoon_minute=0;
    int    m_sunset_minute=0;
    int    m_sunrise_minute=0;
    bool   m_isSunset=false;
    bool   m_isSunrise=false;

     //String fncFormatHHMM(int value);
     
  
public:
    ClsSunset(/* args */);
    ~ClsSunset();
    void   setup_Location(float latitude, float longitude, int dst_Offseet, int dts_dayLight);
    void   loop(DateTime calculate_datetime);
    String getCalculate_YYYYMMDDD_HHMM();
    String getSunsetHHMM();
    String getSunriseHHMM();
    uint   getSunset_minute();
    uint   getSunrise_minute();
    bool   getIsSunset( );
    bool   getIsSunrise();
    void   debug(String callFrom);
  String DateTimeToString_YYMMDD_HHMM(DateTime date);
  String DoubleToString(double dValue);
  
};
#endif