#ifndef CLSTIMESUN_H
#define CLSTIMESUN_H
#include <Arduino.h>
#include "time.h"
#include "esp32/clk.h"
// #include "freertos/timers.h"
#include "Wire.h"
#include "RTClib.h"

#include "ClsSunset.h"
#include <Arduino.h>
#include <WiFi.h>
#include "RemoteDebug.h"
#include "RTClib.h"

// debugI("* -------------   ClsSunset::debug(now)");

// #include <RemoteDebug.h>

// extern RemoteDebug Debug;
//  https://adafruit.github.io/RTClib/html/class_date_time.html
//   https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
//   https://stackoverflow.com/questions/69993920/unable-to-get-time-form-the-ntp-server-in-esp8266-arduino
class ClsTimeRtcNtp
{
private:
  RTC_DS3231 m_Rtc;

  uint32_t m_cpu_freq = esp_clk_cpu_freq();

  DateTime now_LastReaded = DateTime(0, 1, 1, 0, 0, 0); // ñapa, maybe erro in asigned are for not reserve memory
  void fncRtcBegin();
  bool m_NtpReaded = false;
  bool m_Debug = true;
  const unsigned long m_RtcIntervalSwitch = 10000;
  unsigned long m_RtcIntervalPrevious = 0;
  const unsigned long m_NtpIntervalSwitch = 1000000;
  unsigned long m_NtpIntervalPrevious = 0;

  const char *m_NtpServer_default = "pool.ntp.org";
  int m_NtpTimeZone_default = 2;          // hour
  int m_NtpTimeZone_DayLight_default = 1; // add  hour summer
  const int m_NtpTime_HH_2_SS = 3600;

  String m_NtpServer = "pool.ntp.org";
  int m_NtpTimeZone = m_NtpTimeZone_default;
  int m_NtpTimeZoneDayLight = m_NtpTimeZone_DayLight_default;
  double m_NtpLocalGmtOffset_sec = m_NtpTimeZone * m_NtpTime_HH_2_SS;              //(de acuerdo al paralelo)
  double m_NtpLocalDaylightOffset_sec = m_NtpTimeZoneDayLight * m_NtpTime_HH_2_SS; //(De acuedo a reaguste pais)

  // Coordenadas geográficas de Madrid, España, en grados decimales:
  //     Longitud: -3.7025600
  //     Latitud: 40.4165000

  const double m_GpsLatitudeDefault = 40.4165000; // Madrid spain
  const double m_GpsLongitudeDefault = -3.703228; // Madrid spain
  double m_GpsLatitude = 0;
  double m_GpsLongitude = 0;

  // struct tm *m_Time_Local(const time_t *timer)
  struct tm m_Time_Local = {0};
  int m_TimelLocalYear = 0;
  int m_TimelLocalMonth = 0;
  int m_TimelLocalDayMonth = 0;
  int m_TimelLocalDayWeek = 0;

  int m_TimelLocalHour = 0;
  int m_TimelLocalMin = 0;
  int m_TimelLocalSec = 0;
  int m_TimelLocalIdst = 0;
  int m_TimeLocal_MinuteOfDay = 0;
  String m_DateLocalYYYYMMDD = "";
  String m_DateLocalYYYYMMDD_HHMMSS = "";
  String m_TimeLocalHHMM = "";
  DateTime m_NowLastRead = time(0);

  bool IsNight();
  String fncMinutesToHour(double dMinutes);
  String fncFormatYYYYMMDD(int iYear, int iMonth, int iDay);
  String fncFormatHHMMSS(int iHH, int iMM, int iSS);
  String fncTwoDigit(int i);
  void fncFillDateTimevalues();

public:
  ClsTimeRtcNtp(/* args */);
  ~ClsTimeRtcNtp();
  ClsSunset SunSetRise;
  void begin();
  void setup();
  void setup(String ntpServer, int ntpTimeZone, int ntpTimeZoneDayLight, long gpsLatitude, long gpsLongitude);
  void loop(bool bDebug);
  void fncReadNowNTP();
  DateTime nowDateTime_lastRead();
  String NowString();
  String DateTimeToString_YYMMDD_HHMM(DateTime date);
  String DateTimeToString_YYYYMMDD_HHMMSS(DateTime dt);
    String DateTimeToString_YYYYMMDD_HHMM(DateTime dt);
  String DateLocalYYYYMMDD();
  String DateLocalYYYYMMDD_HHMM();
  String TimeLocalHHMM();
  

  DateTime getNowAddDayDateTime(uint addDays);
  enum Period
  {
    IS_WINTER,
    IS_SUMMER
  };
};

#endif