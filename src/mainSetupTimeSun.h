#ifndef MAINSETUPTIMESUN
#define MAINSETUPTIMESUN
#include "mainDefines.h"
#include "WiFi.h"

void fncMainSetupTimeSun()
{
    g_TimeRtcNtp.begin(); // initialize the hardware RTC drivers 
    g_TimeRtcNtp.setup("pool.ntp.org",g_NetworkConfig.get_NtpTimeZone(),g_NetworkConfig.get_NtpTimeZoneDayLight(),g_NetworkConfig.get_GpsLatitude(), g_NetworkConfig.get_GpsLongitude());

    if (WiFi.status() != WL_CONNECTED)
    {
        //setup(String ntpServer, int ntpTimeZone, int ntpTimeZoneDayLight, long gpsLatitude, long gpsLongitude) 
        g_TimeRtcNtp.fncReadNowNTP();
        Serial.println (g_TimeRtcNtp.NowString());
       
     }
}
#endif