#include "ClsNetworkConfig.h"
#include <string>
ClsNetworkConfig::ClsNetworkConfig()
{
}
void ClsNetworkConfig::set_config_default()
{

    // default values prior read configuration saved
    // Set unique SSID for acces point like NewIOT+[substring of mac address]
    char ssid[18];
    uint64_t chipid = ESP.getEfuseMac(); // The chip ID is essentially its MAC address(length: 6 bytes).
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(ssid, 16, "Irrigation-%04X", chip);
    m_WiFI_HostName = m_WiFI_HostName_default;
    // default values for access point mode
    m_WiFI_AP_Ssid = String(ssid);

    m_WiFI_AP_Pwd = m_WiFI_AP_Pwd_default; //=null
    m_WiFI_AP_IP = m_WiFI_AP_IP_default;
    m_WiFI_AP_Mask = m_WiFI_AP_Mask_default;
    m_WiFI_AP_Gateway = m_WiFI_AP_Gateway_default;
    m_WiFI_AP_DNS1 = m_WiFI_AP_DNS1_default;
    m_WiFI_AP_DNS2 = m_WiFI_AP_DNS2_default;
    // default values for workstation mode
    m_WiFI_WS_Ssid = m_WiFI_WS_Ssid_default;
    m_WiFI_WS_Pwd = m_WiFI_WS_Pwd_default;
    m_WiFI_WS_IP = m_WiFI_WS_IP_default;
    m_WiFI_WS_Mask = m_WiFI_WS_Mask_default;
    m_WiFI_WS_Gateway = m_WiFI_WS_Gateway_default;
    m_WiFI_WS_DNS1 = m_WiFI_WS_DNS1_default;
    m_WiFI_WS_DNS2 = m_WiFI_WS_DNS2_default;
    m_GpsLatitude = m_GpsLatitude_default;
    m_GpsLongitude = m_GpsLongitude_default;
    m_NtpTimeZone = m_NtpTimeZone_default;
    m_NtpTimeZoneDayLight = m_NtpTimeZoneDayLight_default;
    m_GpsLatitude = m_GpsLatitude_default;
    m_GpsLongitude = m_GpsLongitude_default;

    //  debug("set_config_default()");
}

//-----------------------------
void ClsNetworkConfig::set_config_AP(String wifi_AP_Ssid, String wifi_AP_Pwd)
{
    m_WiFI_AP_Ssid = wifi_AP_Ssid;
    m_WiFI_AP_Pwd = wifi_AP_Pwd;
}

//----------------------------------------------------------------------------------------------
/// @brief  Confituration for connect to your WiFi access point, IP and gateway by default
/// @param wifi_WS_Ssid String, Name of your wifi
/// @param wifi_WS_Pwd  String, Password connect to your wifi
/// @return
bool ClsNetworkConfig::set_config_WS(String wifi_WS_Ssid, String wifi_WS_Pwd)
{
    m_WiFI_WS_Ssid = wifi_WS_Ssid;
    m_WiFI_WS_Pwd = wifi_WS_Pwd;
    ClsFileSpiffs::fileWrite(m_pathWsSsid, m_WiFI_WS_Ssid);
    ClsFileSpiffs::fileWrite(m_pathWsPass, m_WiFI_WS_Pwd);
    return true;
}
/// @brief  Confituration for connect to your Wifi access point, with fixed IP, Maskc  and Gateway
/// @param wifi_WS_Ssid
/// @param wifi_WS_Pwd
/// @param wifi_WS_IP
/// @param Wifi_AP_Mask
/// @param wifi_AP_Gateway
/// @return true if is set

bool ClsNetworkConfig::set_config_WS(String wifi_WS_Ssid, String wifi_WS_Pwd, IPAddress wifi_WS_IP, IPAddress Wifi_WS_Mask, IPAddress wifi_WS_Gateway)
{
    debugI("Saving network configuration");
    m_WiFI_WS_Ssid = wifi_WS_Ssid;
    m_WiFI_WS_Pwd = wifi_WS_Pwd;
    m_WiFI_WS_IP = wifi_WS_IP;
    m_WiFI_WS_Mask = Wifi_WS_Mask;
    m_WiFI_WS_Gateway = wifi_WS_Gateway;
    ClsFileSpiffs::fileWrite(m_pathWsSsid, m_WiFI_WS_Ssid);
    ClsFileSpiffs::fileWrite(m_pathWsPass, m_WiFI_WS_Pwd);
    ClsFileSpiffs::fileWrite(m_pathWsIP, m_WiFI_WS_IP.toString());
    ClsFileSpiffs::fileWrite(m_pathWsMask, m_WiFI_WS_Mask.toString());
    ClsFileSpiffs::fileWrite(m_pathWsGateway, m_WiFI_WS_Gateway.toString());

    // TODO CHECK IF IS SAVED AND CHECK IF VALID CONFIGURATION
    return true;
}

bool ClsNetworkConfig::set_config_TimeRtcNtp(int ntpTimeZone, int ntpTimeZoneDayLight, double gpsLatitude, double gpsLongitude)
{
    debugI("Saving RTC NTP Configuration");

    m_NtpTimeZone = ntpTimeZone;
    m_NtpTimeZoneDayLight = ntpTimeZoneDayLight;
    m_GpsLatitude = gpsLatitude;
    m_GpsLongitude = gpsLongitude;
    ClsFileSpiffs::fileWrite(m_pathTimeZone, String(m_NtpTimeZone));
    ClsFileSpiffs::fileWrite(m_pathTimeDayLight, String(m_NtpTimeZoneDayLight));

    char cLatitude[14];
    char cLongitude[14];
    dtostrf(m_GpsLatitude, 12, 7, cLatitude);
    dtostrf(m_GpsLongitude, 12, 7, cLongitude);
    ClsFileSpiffs::fileWrite(m_pathLatitude, String(cLatitude));
    ClsFileSpiffs::fileWrite(m_pathLongitude, String(cLongitude));
    return true;
}
//-----------------------------------------------------------------------

bool ClsNetworkConfig::connectAP()
{
    debugI("Enabling Access Point mode with SSID %s, password %s", m_WiFI_AP_Ssid.c_str(), m_WiFI_AP_Pwd.c_str());
    WiFi.disconnect();
    WiFi.mode(WIFI_MODE_AP);
    // bool softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
    if (!WiFi.softAPConfig(m_WiFI_AP_IP, m_WiFI_AP_Gateway, m_WiFI_AP_Mask))
    {
        debugE("AP Failed to configure");
    }
    WiFi.softAP(m_WiFI_AP_Ssid.c_str(), m_WiFI_AP_Pwd.c_str());
    m_WiFi_ConnectedModeLast = 'a';
    m_intervaPrevious = millis();
    return true;
}

//------------------------------------
bool ClsNetworkConfig::connectWS()
{
    debugI("Connecting WiFi as workstation");
    if (m_WiFI_WS_Ssid == "")
    {
        debugI("no SSID configured, skipping workstation connect");
        return false;
    }

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);

    if (!WiFi.config(m_WiFI_WS_IP, m_WiFI_WS_Gateway, m_WiFI_WS_Mask, m_WiFI_WS_DNS2, m_WiFI_WS_DNS2))
    {
        debugE("STA Failed to configure");
    }

    debugI("Connecting as STA to WiFi: %s", m_WiFI_WS_Ssid.c_str());
    WiFi.begin(m_WiFI_WS_Ssid.c_str(), m_WiFI_WS_Pwd.c_str());

    unsigned long m_intervalCurrent = millis();
    m_intervaPrevious = m_intervalCurrent;

    while (WiFi.status() != WL_CONNECTED)
    {
        m_intervalCurrent = millis();

        if (m_intervalCurrent - m_intervaPrevious >= m_interval)
        {
            debugE("WiFi error connecting as STA to %s", m_WiFI_WS_Ssid.c_str());
            m_intervaPrevious = millis();
            m_WiFi_ConnectedModeLast = 'f';
            return false;
        }
        delay(100);
    }
    debugI("WiFi connected successfully as STA, SSID: %s, IP address: %s Gateway: %s Dns: %s", 
          WiFi.SSID().c_str(),
          WiFi.localIP().toString().c_str(),
          WiFi.gatewayIP().toString().c_str(),
          WiFi.dnsIP().toString().c_str());

    m_WiFi_ConnectedModeLast = 'w';
    IsInternetAvailableTest();
    m_intervaPrevious = millis();
    return true;
    ;
}
bool ClsNetworkConfig::setup(int8_t pinReset, bool bForceReset)
{
    m_pinReset = pinReset;
    // if is set pin reset read
    if (digitalRead(m_pinReset) == LOW)
    {
        bForceReset = true;
    }
    // reset factory
    if (bForceReset)
    {
        debugI("Performing factory reset");
        ClsFileSpiffs::fileDelete(m_pathHostName);
        ClsFileSpiffs::fileDelete(m_pathLatitude);
        ClsFileSpiffs::fileDelete(m_pathLongitude);
        ClsFileSpiffs::fileDelete(m_pathRelaysJson);
        ClsFileSpiffs::fileDelete(m_pathTimeDayLight);
        ClsFileSpiffs::fileDelete(m_pathTimeZone);
        ClsFileSpiffs::fileDelete(m_pathWsDns1);
        ClsFileSpiffs::fileDelete(m_pathWsDns2);
        ClsFileSpiffs::fileDelete(m_pathWsGateway);
        ClsFileSpiffs::fileDelete(m_pathWsIP);
        ClsFileSpiffs::fileDelete(m_pathWsMask);
        ClsFileSpiffs::fileDelete(m_pathWsSsid);
        ClsFileSpiffs::fileDelete(m_pathWsPass);
        set_config_default();
        set_config_AP(m_WiFI_AP_Ssid, m_WiFI_AP_Pwd_default);

        set_config_WS(m_WiFI_WS_Ssid, m_WiFI_WS_Pwd, m_WiFI_WS_IP, m_WiFI_WS_Mask, m_WiFI_WS_Gateway);
        set_config_TimeRtcNtp(m_NtpTimeZone, m_NtpTimeZoneDayLight, m_GpsLatitude, m_GpsLongitude);
    }


    if (!configRead())
    {
        debugI("Config read failed, creating one with default value");
        return false;
    }

    return connect_WS_Or_AP();
    ;
}
bool ClsNetworkConfig::connect_WS_Or_AP()
{
    debugI("Trying to enable WiFi as workstation or AP");
    if (connectWS())
    {
        m_WiFi_ConnectedModeLast = 'w';

        return true;
    }
    else
    {
        connectAP();
        m_WiFi_ConnectedModeLast = 'a';
        m_IsInternetAvailable = false;
        return false;
    }
}
//----------------------------------------------------
String ClsNetworkConfig::getWiFiListOfNetworkHtml()

{
    String szReturn;
    int n = WiFi.scanNetworks();
    if (n == 0)
    {
        szReturn = "no networks found";
    }
    else
    {
        szReturn = "<table>";
        szReturn += "<tr><td>Num</td><td>ssid</td><td>rssi</td><td>encription</td></tr>";
        for (int i = 0; i < n; ++i)
        {
            szReturn += "<tr><td>";
            szReturn += String(i + 1);
            szReturn += "</td><td>";
            szReturn += WiFi.SSID(i);
            szReturn += "</td><td>";
            szReturn += (WiFi.RSSI(i));
            szReturn += "</td><td>";
            szReturn += "</td></tr>";
        }
        szReturn += "</table>";
    }
    return szReturn;
}
// TODO

/// @brief  If wifi connection are lost try reconnect
void ClsNetworkConfig::loop()
{
    // if (strcmp(ssidwifi,"SmartCentral") == 0 )
    if ((WiFi.status() == WL_CONNECTED) && m_WiFi_ConnectedModeLast == 'w')
    {
        return;
    }

    m_intervalCurrent = millis();

    // check for overflow in the counters
    if (m_intervaPrevious > m_intervalCurrent)
    {
        debugI("ClsNetworkConfig::loop() Interval roll-over");
        m_intervaPrevious = 0;
    }

    // if in AP mode try to reconnect to wifi if interval is reached
    if (m_intervalCurrent - m_intervaPrevious >= m_interval)
    {
        if (m_WiFi_ConnectedModeLast == 'a' && WiFi.softAPgetStationNum() == 0)
        {
            debugW("WARNING! trying to reconnect to wifi %s", m_WiFI_WS_Ssid.c_str());
            WiFi.disconnect();
            connect_WS_Or_AP();
        }
    }
}

bool ClsNetworkConfig::configRead()
{
    set_config_default();
    // if not exist file then write with default value

    m_WiFI_WS_Ssid = ClsFileSpiffs::fileReadWithDefault(m_pathHostName, m_WiFI_HostName_default);

    m_WiFI_WS_Ssid = ClsFileSpiffs::fileReadWithDefault(m_pathWsSsid, m_WiFI_WS_Ssid_default);

    m_WiFI_WS_Pwd = ClsFileSpiffs::fileReadWithDefault(m_pathWsPass, m_WiFI_WS_Pwd_default);

    m_WiFI_WS_IP.fromString(ClsFileSpiffs::fileReadWithDefault(m_pathWsIP, m_WiFI_WS_IP_default.toString()));

    m_WiFI_WS_Mask.fromString(ClsFileSpiffs::fileReadWithDefault(m_pathWsMask, m_WiFI_WS_Mask_default.toString()));

    m_WiFI_WS_Gateway.fromString(ClsFileSpiffs::fileReadWithDefault(m_pathWsGateway, m_WiFI_WS_Gateway_default.toString()));

    m_WiFI_WS_DNS1.fromString(ClsFileSpiffs::fileReadWithDefault(m_pathWsDns1, m_WiFI_WS_DNS1_default.toString()));

    m_WiFI_WS_DNS2.fromString(ClsFileSpiffs::fileReadWithDefault(m_pathWsDns2, m_WiFI_WS_DNS2_default.toString()));

    m_NtpTimeZone = ClsFileSpiffs::fileReadWithDefault(m_pathTimeZone, String(m_NtpTimeZone_default)).toInt();
    m_NtpTimeZoneDayLight = ClsFileSpiffs::fileReadWithDefault(m_pathTimeDayLight, String(m_NtpTimeZoneDayLight_default)).toInt();

    m_GpsLatitude = ClsFileSpiffs::fncFileReadValueDoubleDefault(m_pathLatitude, m_GpsLatitude_default);

    m_GpsLongitude = ClsFileSpiffs::fncFileReadValueDoubleDefault(m_pathLongitude, m_GpsLongitude_default);
   // debug("configRead");
    return true;
}

//------------------------------------------------------------
char ClsNetworkConfig::get_connectedModeLast()
{
    return m_WiFi_ConnectedModeLast;
}

String ClsNetworkConfig::getWiFiWsSSid() { return m_WiFI_WS_Ssid; }
String ClsNetworkConfig::getWiFiWsPwd() { return m_WiFI_WS_Pwd; }
String ClsNetworkConfig::getWiFiWsIP() { return m_WiFI_WS_IP.toString(); }
String ClsNetworkConfig::getWiFiWsMask() { return m_WiFI_WS_Mask.toString(); }
String ClsNetworkConfig::getWiFiWsGat() { return m_WiFI_WS_Gateway.toString(); }

IPAddress ClsNetworkConfig::getWiFiWsIPAdd() { return m_WiFI_WS_IP; }
IPAddress ClsNetworkConfig::getWiFiWsMaskAdd() { return m_WiFI_WS_Mask; }
IPAddress ClsNetworkConfig::getWiFiWsGatAdd() { return m_WiFI_WS_Gateway; }
IPAddress ClsNetworkConfig::getWiFiWsDNS1Add() { return m_WiFI_WS_DNS1; }
IPAddress ClsNetworkConfig::getWiFiWsDNS2Add() { return m_WiFI_WS_DNS2; }

String ClsNetworkConfig::getWiFiApSsid() { return m_WiFI_AP_Ssid; }
String ClsNetworkConfig::getWiFiApPwd() { return m_WiFI_AP_Pwd; };
String ClsNetworkConfig::getWiFiApIP() { return m_WiFI_AP_IP.toString(); }
String ClsNetworkConfig::getWiFiApMask() { return m_WiFI_AP_Mask.toString(); }
String ClsNetworkConfig::getWiFiApGateway() { return m_WiFI_AP_Gateway.toString(); }

IPAddress ClsNetworkConfig::getWiFiApIPAdd() { return m_WiFI_AP_IP; }
IPAddress ClsNetworkConfig::getWiFiApMaskAdd() { return m_WiFI_AP_Mask; }
IPAddress ClsNetworkConfig::getWiFiApGatAdd() { return m_WiFI_AP_Gateway; }

String ClsNetworkConfig::getNtpTimeZone() { return String(m_NtpTimeZone); }
String ClsNetworkConfig::getNtpTimeZoneDayLight() { return String(m_NtpTimeZoneDayLight); }
String ClsNetworkConfig::getGpsLongitude()
{
    char aBuffer14[14];
    dtostrf(m_GpsLongitude, 12, 7, aBuffer14);
    String sBuffer = String(aBuffer14);
    sBuffer.trim();
    return sBuffer;
}
String ClsNetworkConfig::getGpsLatitude()
{
    char aBuffer14[14];
    dtostrf(m_GpsLatitude, 12, 7, aBuffer14);
    String sBuffer = String(aBuffer14);
    sBuffer.trim();
    return sBuffer;
}

int ClsNetworkConfig::get_NtpTimeZone() { return m_NtpTimeZone; }
int ClsNetworkConfig::get_NtpTimeZoneDayLight() { return m_NtpTimeZoneDayLight; }
double ClsNetworkConfig::get_GpsLatitude() { return m_GpsLatitude; }
double ClsNetworkConfig::get_GpsLongitude() { return m_GpsLongitude; }

String ClsNetworkConfig::getConfigFull()
{

    // dtostrf(m_GpsLatitude, 12, 7, buffer12_latitude); // 2 position for signed and \0
    // dtostrf(m_GpsLongitude, 12, 7, buffer12_longitude);
    String fill = "";
    fill = m_WiFI_WS_Ssid + "#" + m_WiFI_WS_Pwd + "#" + m_WiFI_WS_IP.toString() + "#" + m_WiFI_WS_Mask.toString() + "#" + m_WiFI_WS_Gateway.toString() + "#" + String(m_NtpTimeZone) + "#" + String(m_NtpTimeZoneDayLight) + "#" + getGpsLatitude() + "#" + getGpsLongitude();
    return fill;
}
String ClsNetworkConfig::getConfigDefaultFull()
{
    char buffer12_latitudeDefault[14];                               // extra for \0 or signus
    char buffer12_longitudeDefault[14];                              // extra for \0 or signus
    dtostrf(m_GpsLatitude_default, 12, 7, buffer12_latitudeDefault); // 2 position for signed and \0
    dtostrf(m_GpsLongitude_default, 12, 7, buffer12_longitudeDefault);
    String fill = "";
    fill = m_WiFI_WS_Ssid_default + "#" + m_WiFI_WS_Pwd_default + "#" + m_WiFI_WS_IP_default.toString() + "#" + m_WiFI_WS_Mask_default.toString() + "#" + m_WiFI_WS_Gateway.toString() + "#" + String(m_NtpTimeZone_default) + "#" + String(m_NtpTimeZoneDayLight_default) + "#" + String(buffer12_latitudeDefault) + "#" + String(buffer12_longitudeDefault);
    return fill;
}
bool ClsNetworkConfig::IsInternetAvailable() { return m_IsInternetAvailable; }
bool ClsNetworkConfig::IsInternetAvailableTest()
{
    bool test = false;
    const char *remote_host = "www.google.com";
    const char *remote_host2 = "dns.google.com";
    const IPAddress remote_ip(8, 8, 4, 4);
    debugI("Ping test connection internet (to 8.8.4.4)");
    if (Ping.ping(remote_ip))
    {
        debugI("ping 8.8.4.4 Success!!");
        test = true;
    }
    else if (Ping.ping(remote_host))
    {
        debugI("ping www.google.com Success!!");
        test = true;
    }
    else if (Ping.ping(remote_host2))
    {
        debugI("ping dns.google.com Success!!");
        test = true;
    }
    m_IsInternetAvailable = test;

    if (m_IsInternetAvailable)
    {
        debugI("Internet connection available");
    }
    else
    {
        debugW("Internet connection NOT available");
    }
    return m_IsInternetAvailable;
}

void ClsNetworkConfig::debug(String from)
{
    
    debugV("====================");
    debugV("debug ClsWificonfig %s", from.c_str());

    debugV("====================");
    debugV(".");
    debugV("m_WiFI_HostName=%s", m_WiFI_HostName.c_str());
    debugV("m_WiFI_AP_Pwd=%s", m_WiFI_AP_Pwd.c_str());
    debugV("m_WiFI_AP_Ssid=%s", m_WiFI_AP_Ssid.c_str());
    debugV("m_WiFI_AP_Pwd=%s", m_WiFI_AP_Pwd.c_str());
    debugV(".");
    debugV("m_WiFI_WS_Ssid=%s", m_WiFI_WS_Ssid.c_str());
    debugV("m_WiFI_WS_Pwd=%s", m_WiFI_WS_Pwd.c_str());
    debugV(".");
    debugV("WiFi.localIP()=%s", WiFi.localIP().toString().c_str());
    debugV("WiFi.getMode()=%d", WiFi.getMode());
    debugV("WiFi.getHostname()=%s", WiFi.getHostname());
    debugV("WiFi.gatewayIP()=%s", WiFi.gatewayIP().toString().c_str());
    debugV("WiFi.getAutoReconnect()=%d", WiFi.getAutoReconnect());
    debugV("m_GpsLatitude=%f", m_GpsLatitude);
    debugV("m_GpsLongitude=%f", m_GpsLongitude);
    debugV(".");
    debugV("m_NtpTimeZone=%d", m_NtpTimeZone);
    debugV("m_NtpTimeZoneDayLight=%d", m_NtpTimeZoneDayLight);
    debugV("m_IsInternetAvailable=%d", m_IsInternetAvailable);
    debugV("====================");
}

String ClsNetworkConfig::fncIpAddressToString(IPAddress ipAddress)
{
    ipAddress.toString();
    String result = String(ipAddress[0]) + "." + String(ipAddress[1]) + String(ipAddress[3]) + String(ipAddress[3]);

    return result;
}
IPAddress ClsNetworkConfig::fncIpAddressFromString(String ipAddressString)
{
    IPAddress ip;
    ip.fromString(ipAddressString);
    return ip;
}
