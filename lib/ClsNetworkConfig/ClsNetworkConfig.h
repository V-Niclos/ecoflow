#ifndef ClsWifiConfig_H
#define ClsWifiConfig_H
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>
#include "SPIFFS.h"
#include "ESP32Ping.h" // foe internet is available
#include "ClsFileSpiffs.h"
#include <string>
#include "RemoteDebug.h"
#include "secret.h"
extern RemoteDebug Debug;

/// @brief
class ClsNetworkConfig
{
public:
    ClsNetworkConfig();
    bool setup(bool bResetToDefaultAndSave);
    /// @brief  call in your loop, at intervals update time from NTP server and
    //  calculate sunshine, sunset, momfase and if is daty
    void loop(bool isReset);
    void set_config_AP(String wifi_AP_Ssid, String wifi_AP_Pwd);
    bool set_config_WS(bool bSave, String wifi_Host_Name, String wifi_WS_Ssid, String wifi_WS_Pwd);
    bool set_config_TimeRtcNtp(bool bSave, int ntpTimeZone, int ntpTimeZoneDayLight, double GpsLongitude, double gpsLatitude);

    void set_config_default(bool bResetToDefaultAndSave);
    void debug(String from);
    String macAddress = WiFi.macAddress();
    String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
    String getWiFiListOfNetworkHtml();
    String gethostname();
    bool getUseDHCP();
    String getWiFiWsSSid();
    String getWiFiWsPwd();

    String getWiFiApSsid();
    String getWiFiApPwd();

    int get_NtpTimeZone();
    int get_NtpTimeZoneDayLight();
    double get_GpsLatitude();
    double get_GpsLongitude();

    String getNtpTimeZone();
    String getNtpTimeZoneDayLight();
    String getGpsLongitude();
    String getGpsLatitude();
    String getGpsLongitude_default();
    String getGpsLatitude_default();
    String getConfigFull();
    String getConfigDefaultFull();
    char get_connectedModeLast();

    bool IsInternetAvailable();
    bool IsInternetAvailableTest();

    /// @brief  Obtain ip4 public if device are connected to Internet
    /// @return 
    String GetPublicIP();

private:
    // String m_RelaysJson_default = "[{\"idRelay\":\"0\", \"Name\": \"Belen 1\", \"Mode\": \"2\", \"Time\":\"0\"}, {\"idRelay\":\"1\", \"Name\": \"Belen 2\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"2\", \"Name\": \"Belen 3\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"3\", \"Name\": \"Belen 4\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"4\", \"Name\": \"Belen 5\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"5\", \"Name\": \"Belen 6\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"6\", \"Name\": \"Belen 7\", \"Mode\": \"0\", \"Time\":\"3\"}, {\"idRelay\":\"7\", \"Name\": \"Belen 8\", \"Mode\": \"0\", \"Time\":\"3\"}]";

    // AP for Access point mode
    // -1= not establised, not in use
    //-----------------------------
    // default values for access point mode
    // m_WiFi_AP_Ssid_default  is buidl automatic
    // with "flow" + four digits of  ESP.getEfuseMac()
    const String m_WiFi_Host_Name_default = HOST_NAME;
    const String m_WiFi_AP_Pwd_default =AP_PWD ; //=null

    // default values for workstation mode
    const String m_WiFi_WS_Ssid_default = WS_1_SSID;
    const String m_WiFi_WS_Pwd_default = WS_1_PWD;

    const String m_WiFi_WS_Ssid_default2 = WS_2_SSID;
    const String m_WiFi_WS_Pwd_default2 = WS_2_PWD;

    char m_WiFi_ConnectedModeLast = 'f'; // f=false, not connected, w=workstation, a=access  point
    long m_interval = 30000;             // 1/2 minute
    long m_intervaPrevious = 0;
    long m_intervalCurrent = 0;

    String m_WiFi_Host_Name = "";
    bool m_IsInternetAvailable = false;

    String m_WiFi_AP_Ssid = "";
    String m_WiFi_AP_Pwd = "";
    // WS Work station mode
    String m_WiFi_WS_Ssid = "";
    String m_WiFi_WS_Pwd = "";
    const String m_WiFi_WS_Ssid2 = m_WiFi_WS_Ssid_default2;
    const String m_WiFi_WS_Pwd2 = m_WiFi_WS_Pwd_default2;

    //-----------------------------
    /*
Cabanillas de la sierra
 Longitud: -3.6367800
 Latitud: 40.8257000
 Madrid
Longitud: -3.7025600
Latitud: 40.4165000
 */
    const int m_NtpTimeZone_default = 1;
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
    bool connectWS(String wifiSsid, String wifiPWd);

    bool configRead();
    bool connect_WS_Or_AP();

    // each parameters is saved in diferent file path
    // each file only has one parameter
    const char *m_pathHostName = "/hostname.txt";
    const char *m_pathWsSsid = "/wsssid.txt";
    const char *m_pathWsPass = "/wspwd.txt";

    const char *m_pathTimeZone = "/timezone.txt";
    const char *m_pathTimeDayLight = "/timedaylight.txt";
    const char *m_pathLatitude = "/latitude.txt";
    const char *m_pathLongitude = "/longitude.txt";
    const char *m_pathRelaysJson = "/relaysjson.txt";
    String fncIpAddressToString(IPAddress ipAddress);
    IPAddress fncIpAddressFromString(String ipAddressString);
    void fncResetFactory();
};
#endif