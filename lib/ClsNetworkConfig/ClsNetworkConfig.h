#ifndef ClsWifiConfig_H
#define ClsWifiConfig_H
#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "ESP32Ping.h" // foe internet is available

/// @brief
class ClsNetworkConfig
{
public:
    ClsNetworkConfig();
    bool setup(int8_t pinReset, bool bForceReset);
    void set_config_AP(String wifi_AP_Ssid, String wifi_AP_Pwd);
    bool set_config_WS(String wifi_WS_Ssid, String wifi_WS_Pwd);
    bool set_config_WS(String wifi_WS_Ssid, String wifi_WS_Pwd, IPAddress wifi_WS_IP, IPAddress Wifi_AP_Mask, IPAddress wifi_AP_Gateway);
    bool set_config_TimeRtcNtp(int ntpTimeZone, int ntpTimeZoneDayLight, double GpsLongitude, double gpsLatitude);

    void set_config_default();
    void debug(String from);
    String macAddress = WiFi.macAddress();
    String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
    String getWiFiListOfNetworkHtml();
    String getWiFiWsSSid();
    String getWiFiWsPwd();
    String getWiFiWsIP();
    String getWiFiWsMask();
    String getWiFiWsGat();
    String getWiFiWsDNS1();
    String getWiFiWsDNS2();
    IPAddress getWiFiWsIPAdd();
    IPAddress getWiFiWsMaskAdd();
    IPAddress getWiFiWsGatAdd();
    IPAddress getWiFiWsDNS1Add();
    IPAddress getWiFiWsDNS2Add();

    String getWiFiApSsid();
    String getWiFiApPwd();
    String getWiFiApIP();
    String getWiFiApMask();
    String getWiFiApGateway();

    IPAddress getWiFiApIPAdd();
    IPAddress getWiFiApMaskAdd();
    IPAddress getWiFiApGatAdd();

/*
 m_NtpTimeZone = ntpTimeZone;
    m_NtpTimeZoneDayLight = ntpTimeZoneDayLight;
    m_GpsLatitude = gpsLatitude;
    m_GpsLongitude = gpsLongitude;
 bool set_config_TimeRtcNtp(int ntpTimeZone, int ntpTimeZoneDayLight, double GpsLongitude, double gpsLatitude);

*/
 int get_NtpTimeZone();
 int get_NtpTimeZoneDayLight ();
 double get_GpsLatitude() ;
 double get_GpsLongitude();

    String getNtpTimeZone();
    String getNtpTimeZoneDayLight();
    String getGpsLongitude();
    String getGpsLatitude();
    String getConfigFull();
    String getConfigDefaultFull();
    char get_connectedModeLast();

    bool IsInternetAvailable();
    bool IsInternetAvailableTest();
  

    /// @brief  call in your loop, at intervals update time from NTP server and
    //  calculate sunshine, sunset, momfase and if is daty
    void loop();

private:
    // String m_RelaysJson_default = "[{\"idRelay\":\"0\", \"Name\": \"Belen 1\", \"Mode\": \"2\", \"Time\":\"0\"}, {\"idRelay\":\"1\", \"Name\": \"Belen 2\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"2\", \"Name\": \"Belen 3\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"3\", \"Name\": \"Belen 4\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"4\", \"Name\": \"Belen 5\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"5\", \"Name\": \"Belen 6\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"6\", \"Name\": \"Belen 7\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"7\", \"Name\": \"Belen 8\", \"Mode\": \"0\", \"Time\":\"3\"}]";

    // AP for Access point mode

    int8_t m_pinReset = -1;              // -1= not establised, not in use
    char m_WiFi_ConnectedModeLast = 'f'; // f=false, not connected, w=workstation, a=access  point
    long m_interval = 5000;
    long m_intervaPrevious = 0;
    long m_intervalCurrent = 0;

    bool m_IsInternetAvailable = false;
    String m_WiFI_AP_Ssid = "";
    String m_WiFI_AP_Pwd = "";
    IPAddress m_WiFI_AP_IP;
    IPAddress m_WiFI_AP_Mask;
    IPAddress m_WiFI_AP_Gateway;
    IPAddress m_WiFI_AP_DNS1;
    IPAddress m_WiFI_AP_DNS2;

    // WS Work station mode
    String m_WiFI_WS_Ssid = "";
    String m_WiFI_WS_Pwd = "";
    IPAddress m_WiFI_WS_IP;
    IPAddress m_WiFI_WS_Mask;
    IPAddress m_WiFI_WS_Gateway;
    IPAddress m_WiFI_WS_DNS1;
    IPAddress m_WiFI_WS_DNS2;
    //-----------------------------
    // default values for access point mode
    // m_WiFI_AP_Ssid_default  is buidl automatic
    // with "NewIOt" + four digits of  ESP.getEfuseMac()
    String m_WiFI_AP_Pwd_default = "123456789"; //=null
    IPAddress m_WiFI_AP_IP_default = {192, 168, 1, 1};
    IPAddress m_WiFI_AP_Mask_default = {255, 255, 255, 0};
    IPAddress m_WiFI_AP_Gateway_default = {192, 168, 1, 1};
    IPAddress m_WiFI_AP_DNS1_default = {192, 168, 1, 1};
    IPAddress m_WiFI_AP_DNS2_default = {192, 168, 1, 1};
    // default values for workstation mode
    String m_WiFI_WS_Ssid_default = "testudines";
    String m_WiFI_WS_Pwd_default = "915265ABCD";
    IPAddress m_WiFI_WS_IP_default = {192, 168, 2, 254};
    IPAddress m_WiFI_WS_Mask_default = {255, 255, 255, 0};
    IPAddress m_WiFI_WS_Gateway_default = {192, 168, 2, 1};
    IPAddress m_WiFI_WS_DNS1_default = {8, 8, 8, 8};
    IPAddress m_WiFI_WS_DNS2_default = {8, 8, 4, 4};
    //-----------------------------
       /*
   Cabanillas de la sierra
    Latitud: -3.6367800
    Longitud: 40.8257000
    */
    const int m_NtpTimeZone_default = 2;
    int m_NtpTimeZone = m_NtpTimeZone_default;
    const int m_NtpTimeZoneDayLight_default = 1;
    int m_NtpTimeZoneDayLight = m_NtpTimeZoneDayLight_default;
    const double m_GpsLatitude_default = 40.8257000;
    double m_GpsLatitude = m_GpsLatitude_default;
    const double m_GpsLongitude_default = -3.6367800;
    double m_GpsLongitude = m_GpsLongitude_default;
    //----------------------------------

    //-----------------------------

    bool connectAP();
    bool connectWS();
    bool configRead();
    bool connect_WS_Or_AP();

    bool fncFileExist(String filePaht);

    // each parameters is saved in diferent file path
    // each file only has one parameter
    const char *m_pathSsid = "/ssid.txt";
    const char *m_pathPass = "/pwd.txt";
    const char *m_pathIP = "/ip.txt";
    const char *m_pathMask = "/mask.txt";
    const char *m_pathGateway = "/gateway.txt";
    const char *m_pathDns1 = "/dns1.txt";
    const char *m_pathDns2 = "/dns2.txt";
    const char *m_pathTimeZone = "/timezone.txt";
    const char *m_pathTimeDayLight = "/timedaylight.txt";
    const char *m_pathLatitude = "/latitude.txt";
    const char *m_pathLongitude = "/longitude.txt";
    const char *m_pathPinReset = "/pinreset.txt";
    const char *m_pathRelaysJson = "/relaysjson.txt";
    bool fncFileSpiffsInit();
    String fncFileReadValue(fs::FS &fs, const char *path);
    double fncFileReadValueDouble(fs::FS &fs, const char *path);
    void fncFileWriteValue(fs::FS &fs, const char *path, const char *value);
};
#endif