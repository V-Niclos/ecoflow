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

    // Serial.println(wifi_WS_Gateway);

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

    Serial.println("web post recived 1b ");
    Serial.println(m_WiFI_WS_Ssid);
    Serial.println(m_WiFI_WS_Pwd);
    Serial.println(m_WiFI_WS_IP);
    // TODO CHECK IF IS SAVED AND CHECK IF VALID CONFIGURATION
    return true;
}

bool ClsNetworkConfig::set_config_TimeRtcNtp(int ntpTimeZone, int ntpTimeZoneDayLight, double gpsLatitude, double gpsLongitude)
{
    Serial.println("--------------------");
    Serial.println("ClsNetworkConfig::set_config_TimeRtcNtp recived parameters");
    Serial.print("gpsLatitude)= ");
    Serial.print(gpsLatitude, 9);
    Serial.print("gpsLongitude)= ");
    Serial.println(gpsLongitude, 9);

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
    WiFi.disconnect();
    WiFi.mode(WIFI_MODE_AP);
    // bool softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
    if (!WiFi.softAPConfig(m_WiFI_AP_IP, m_WiFI_AP_Gateway, m_WiFI_AP_Mask))
    {
        Serial.println("AP Failed to configure");
    }
    WiFi.softAP(m_WiFI_AP_Ssid.c_str(), m_WiFI_AP_Pwd.c_str());
    Serial.println("Wifi connected as ");
    Serial.printf("[WIFI] Access Point Mode, SSID: %s, IP address: %s\n", m_WiFI_AP_Ssid.c_str(), WiFi.softAPIP().toString().c_str());
    m_WiFi_ConnectedModeLast = 'a';
    m_intervaPrevious = millis();
    Serial.printf("connectAP():: m_intervaPrevious: %ld %p\n", m_intervaPrevious, &m_intervaPrevious);
    return true;
}

//------------------------------------
bool ClsNetworkConfig::connectWS()
{
    Serial.println("ClsNetworkConfig::connectWS()");
    if (m_WiFI_WS_Ssid == "")
    {
        Serial.println("no SSID configured, skipping workstation connect");
        return false;
    }

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    // WiFi.mode(WIFI_AP);
    // g_NetWsIpDNS1, g_NetWsIpDNS2
    if (!WiFi.config(m_WiFI_WS_IP, m_WiFI_WS_Gateway, m_WiFI_WS_Mask, m_WiFI_WS_DNS2, m_WiFI_WS_DNS2))
    {
        Serial.println("STA Failed to configure");
    }

    Serial.print("Connecting as STA to WiFi: ");
    Serial.print(m_WiFI_WS_Ssid);
    WiFi.begin(m_WiFI_WS_Ssid.c_str(), m_WiFI_WS_Pwd.c_str());
    unsigned long m_intervalCurrent = millis();
    m_intervaPrevious = m_intervalCurrent;

    while (WiFi.status() != WL_CONNECTED)
    {
        m_intervalCurrent = millis();
        // Serial.print(".");
        if (m_intervalCurrent - m_intervaPrevious >= m_interval)
        {
            // Serial.println("Failed to connect.");
            m_intervaPrevious = millis();
            m_WiFi_ConnectedModeLast = 'f';
            return false;
        }
        delay(100);
    }
    Serial.println("");
    Serial.println("Wifi connected as ");
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s Gateway: %s Dns: %s", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str(), WiFi.gatewayIP().toString(), WiFi.dnsIP().toString());
    Serial.println("");
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
        Serial.println("Reset factory");
        set_config_default();
        set_config_AP(m_WiFI_AP_Ssid, m_WiFI_AP_Pwd_default);

        set_config_WS(m_WiFI_WS_Ssid, m_WiFI_WS_Pwd, m_WiFI_WS_IP, m_WiFI_WS_Mask, m_WiFI_WS_Gateway);
        set_config_TimeRtcNtp(m_NtpTimeZone, m_NtpTimeZoneDayLight, m_GpsLatitude, m_GpsLongitude);
    }

    Serial.println("-------------------------------------ClsNetworkConfig::setup()");

    if (!configRead())
    {
        Serial.println("Not config readed,create one with default values");

        return false;
    }

    return connect_WS_Or_AP();
    ;
}
bool ClsNetworkConfig::connect_WS_Or_AP()
{
    Serial.print("connect_WS_Or_AP()");
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
            // Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
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
        Serial.println("ClsNetworkConfig::loop() Interval roll-over");
        m_intervaPrevious = 0;
    }

    // if in AP mode try to reconnect to wifi if interval is reached
    if (m_intervalCurrent - m_intervaPrevious >= m_interval)
    {
        if (m_WiFi_ConnectedModeLast == 'a' && WiFi.softAPgetStationNum() == 0)
        {
            Serial.println("WARNING! trying to reconnect to wifi " + m_WiFI_WS_Ssid);
            WiFi.disconnect();
            connect_WS_Or_AP();
        }
    }
}

bool ClsNetworkConfig::configRead()
{
    Serial.print("-------------------------------------ClsNetworkConfig::configRead() start:");

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
    debug("configRead");
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
    Serial.println("Ping test connection internet");
    if (Ping.ping(remote_ip))
    {
        Serial.println("ping8, 8, 4, 4 Success!!");
        test = true;
    }
    else if (Ping.ping(remote_host))
    {
        Serial.println("ping www.google.com Success!!");
        test = true;
    }
    else if (Ping.ping(remote_host2))
    {
        Serial.println("ping dns.google.com Success!!");
        test = true;
    }
    m_IsInternetAvailable = test;
    Serial.print("Test if  Internet available");
    if (m_IsInternetAvailable)
    {
        Serial.println(" Succes!");
    }
    else
    {
        Serial.println(" fail!");
    }
    return m_IsInternetAvailable;
}

void ClsNetworkConfig::debug(String from)
{
    Serial.println("====================");
    Serial.println("debug ClsWificonfig" + from);

    Serial.println("====================");
    Serial.println(".");
    Serial.print("m_WiFI_HostName=" + String(m_WiFI_HostName));
    Serial.print("m_WiFI_AP_Pwd=" + String(m_WiFI_AP_Pwd));
    Serial.print("m_WiFI_AP_Ssid=" + String(m_WiFI_AP_Ssid));
    Serial.print("m_WiFI_AP_Pwd=" + String(m_WiFI_AP_Pwd));
    Serial.println(".");
    Serial.print("m_WiFI_WS_Ssid=" + String(m_WiFI_WS_Ssid));
    Serial.print("m_WiFI_WS_Pwd=" + String(m_WiFI_WS_Pwd));
    Serial.println(".");
    Serial.print(WiFi.localIP());
    Serial.println(WiFi.localIP());
    Serial.println("WiFi.getMode()=" + WiFi.getMode());
    Serial.println("WiFi.getHostname()=" + String(WiFi.getHostname()));
    Serial.println("WiFi.gatewayIP()=" + String(WiFi.gatewayIP()));
    Serial.println("WiFi.getAutoReconnect()=" + String(WiFi.getAutoReconnect()));

    Serial.print("m_GpsLatitude=" + String(m_GpsLatitude));
    Serial.print("m_GpsLongitude=" + String(m_GpsLongitude));
    Serial.println(".");
    Serial.print("m_NtpTimeZone=" + String(m_NtpTimeZone));
    Serial.println("m_NtpTimeZone=" + String(m_NtpTimeZoneDayLight));

    Serial.println("m_pinReset=" + String(m_pinReset));

    Serial.println("m_IsInternetAvailable=" + String(m_IsInternetAvailable));
    Serial.println("====================");
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
