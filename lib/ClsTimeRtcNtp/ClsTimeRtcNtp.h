#ifndef CLSTIMESUN_H
#define CLSTIMESUN_H
#include <Arduino.h>
#include "time.h"
#include "freertos/timers.h"
#include "Wire.h"
#include "RTClib.h"
#include <RemoteDebug.h>

extern RemoteDebug Debug;
// https://adafruit.github.io/RTClib/html/class_date_time.html
//  https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
//  https://stackoverflow.com/questions/69993920/unable-to-get-time-form-the-ntp-server-in-esp8266-arduino
class ClsTimeRtcNtp
{
private:
  RTC_DS3231 m_Rtc;

  unsigned long IntervalPreviousRead = 0;
  const unsigned long intervalLapseRead = 1000;

  /*
  DateTime::DateTime 	( 	uint16_t  	year,
      uint8_t  	month,
      uint8_t  	day,
      uint8_t  	hour = 0,
      uint8_t  	min = 0,
      uint8_t  	sec = 0
    )
      year	Either the full year (range: 2000–2099) or the offset from year 2000 (range: 0–99).
      month	Month number (1–12).
      day	Day of the month (1–31).
      hour,min,sec	Hour (0–23), minute (0–59) and second (0–59).
  DateTime t0 (2018,7,14,8,0,0);
  */
  DateTime now_LastReaded = DateTime(0, 1, 1, 0, 0, 0); // ñapa, maybe erro in asigned are for not reserve memory

  void fncRtcBegin();

  bool m_NtpReaded = false;
  unsigned long m_Ntpcounter = 0;
  int64_t m_NtpIntervalSwitch = 100000;
  int64_t m_NtpIntervalPrevious = 0;
  int64_t m_NtpIntervalActual = 0;

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
  String m_TimeLocalHHMM = "";
  DateTime m_NowLastRead;

  bool IsNight();
  String fncMinutesToHour(double dMinutes);
  String fncFormatYYYYMMDD(int iYear, int iMonth, int iDay);
  String fncFormatHHMMSS(int iHH, int iMM, int iSS);
  String fncTwoDigit(int i);
  void fncFillDateTimevalues();

public:
  ClsTimeRtcNtp(/* args */);
  ~ClsTimeRtcNtp();
  void begin();
  void setup();
  void setup(String ntpServer, int ntpTimeZone, int ntpTimeZoneDayLight, long gpsLatitude, long gpsLongitude);
  void loop();
  void fncReadNowNTP();
  void debugSerial();
  DateTime nowDateTime();
  String NowString();

  String DateLocalYYYYMMDD();
  String TimeLocalHHMM();
  DateTime getNowAddDayDateTime(uint addDays);

};

#endif