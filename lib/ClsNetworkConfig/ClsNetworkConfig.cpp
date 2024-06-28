#include "ClsNetworkConfig.h"

ClsNetworkConfig::ClsNetworkConfig()
{
}
void ClsNetworkConfig::set_config_default(bool bResetToDefaultAndSave)
{

    // default values prior read configuration saved
    // Set unique SSID for acces point like NewIOT+[substring of mac address]

    char ssid[32];
    uint32_t chipid = ESP.getEfuseMac(); // The chip ID is essentially its MAC address(length: 6 bytes).
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(ssid, 16, "riego-%04X", chip);
    m_WiFi_Host_Name = m_WiFi_Host_Name_default;

    // default values for access point mode
    m_WiFi_AP_Ssid = String(ssid);
    m_WiFi_AP_Pwd = m_WiFi_AP_Pwd_default; //=null
    // default values for workstation mode
    m_WiFi_WS_Ssid = m_WiFi_WS_Ssid_default;
    m_WiFi_WS_Pwd = m_WiFi_WS_Pwd_default;

    m_GpsLatitude = m_GpsLatitude_default;
    m_GpsLongitude = m_GpsLongitude_default;
    m_NtpTimeZone = m_NtpTimeZone_default;
    m_NtpTimeZoneDayLight = m_NtpTimeZoneDayLight_default;

    m_GpsLatitude = m_GpsLatitude_default;
    m_GpsLongitude = m_GpsLongitude_default;
    // debug("set_config_default() start");

    set_config_WS(bResetToDefaultAndSave, m_WiFi_Host_Name, m_WiFi_WS_Ssid, m_WiFi_WS_Pwd);
    set_config_AP(m_WiFi_AP_Ssid, m_WiFi_AP_Pwd);

    // todo leer desde la configuracion
    // set_config_TimeRtcNtp(bResetToDefaultAndSave, m_NtpTimeZone, m_NtpTimeZoneDayLight, m_GpsLongitude, m_GpsLatitude);
    // Coordenadas madrid 40.4165, -3.70256
    m_GpsLongitude = 40.4165;
    m_GpsLatitude = -3.70256;
    m_NtpTimeZone = 1;         // horario invierno +1
    m_NtpTimeZoneDayLight = 1; // horario verano +2
    set_config_TimeRtcNtp(bResetToDefaultAndSave, m_NtpTimeZone, m_NtpTimeZoneDayLight, m_GpsLongitude, m_GpsLatitude);
    if (bResetToDefaultAndSave)
    {
        debug("set_config_default() and save");
    }
}

//-----------------------------
void ClsNetworkConfig::set_config_AP(String wifi_AP_Ssid, String wifi_AP_Pwd)
{

    m_WiFi_AP_Ssid = wifi_AP_Ssid;
    m_WiFi_AP_Pwd = wifi_AP_Pwd;
}

//----------------------------------------------------------------------------------------------
/// @brief  Confituration for connect to your WiFi access point, IP and gateway by default
/// @param wifi_WS_Ssid String, Name of your wifi
/// @param wifi_WS_Pwd  String, Password connect to your wifi
/// @return
bool ClsNetworkConfig::set_config_WS(bool bSave, String wiFi_Host_Name, String wifi_WS_Ssid, String wifi_WS_Pwd)
{
    m_WiFi_Host_Name = wiFi_Host_Name;
    m_WiFi_WS_Ssid = wifi_WS_Ssid;
    m_WiFi_WS_Pwd = wifi_WS_Pwd;

    if (bSave)
    {
        Serial.println("Setting and Save  network configuration");
        ClsFileSpiffs::fileWrite(m_pathHostName, m_WiFi_Host_Name);
        ClsFileSpiffs::fileWrite(m_pathHostName, m_WiFi_Host_Name);
        ClsFileSpiffs::fileWrite(m_pathWsSsid, m_WiFi_WS_Ssid);
        ClsFileSpiffs::fileWrite(m_pathWsPass, m_WiFi_WS_Pwd);
    }
    else
    {
        Serial.println("Setting only network configuration");
    }

    return true;
}
/// @brief  Confituration for connect to your Wifi access point, with fixed IP, Maskc  and Gateway
/// @param bSave true= setting and  save config in files, false=only setting
/// @param wifiNetHostName  for acces like wifiNetHostName.local using mNDNS
/// On Microsoft Windos you need download and install  -  Bonjour Print Services for Windows
/// https://support.apple.com/kb/DL999?viewlocale=en_US&locale=es_ES

//   bool set_config_TimeRtcNtp(bool bSave,int ntpTimeZone, int ntpTimeZoneDayLight, double GpsLongitude, double gpsLatitude);

bool ClsNetworkConfig::set_config_TimeRtcNtp(bool bSave, int ntpTimeZone, int ntpTimeZoneDayLight, double gpsLongitude, double gpsLatitude)
{
    /// @todo Update Rtc
    m_NtpTimeZone = ntpTimeZone;
    m_NtpTimeZoneDayLight = ntpTimeZoneDayLight;
    m_GpsLatitude = gpsLatitude;
    m_GpsLongitude = gpsLongitude;

    if (bSave)
    {
        ////// debugI("Saving RTC NTP Configuration");
        ClsFileSpiffs::fileWrite(m_pathTimeZone, String(m_NtpTimeZone));
        ClsFileSpiffs::fileWrite(m_pathTimeDayLight, String(m_NtpTimeZoneDayLight));
        char cLatitude[14];
        char cLongitude[14];
        dtostrf(m_GpsLatitude, 12, 7, cLatitude);
        dtostrf(m_GpsLongitude, 12, 7, cLongitude);
        ClsFileSpiffs::fileWrite(m_pathLatitude, String(cLatitude));
        ClsFileSpiffs::fileWrite(m_pathLongitude, String(cLongitude));
    }
    else
    {
        Serial.println("Setting RTC NTP Configuration");
    }

    return true;
}
//-----------------------------------------------------------------------

bool ClsNetworkConfig::connectAP()
{
    Serial.println("Enabling Access Point mode with SSID= " + m_WiFi_AP_Ssid + " password=  " + m_WiFi_AP_Pwd);
    WiFi.disconnect();
    WiFi.mode(WIFI_MODE_AP);

    IPAddress Ip(192, 168, 1, 1);
    IPAddress NMask(255, 255, 255, 0);
    WiFi.softAPConfig(Ip, Ip, NMask);

    WiFi.softAP(m_WiFi_AP_Ssid.c_str(), m_WiFi_AP_Pwd.c_str());
    m_WiFi_ConnectedModeLast = 'a';

    // debugI("Wifi mode AP ipAddress %s", WiFi.softAPIP().toString().c_str());

    m_intervaPrevious = millis();
    return true;
}

//------------------------------------
bool ClsNetworkConfig::connectWS(String wifiSiid, String WifiPwd)
{
    if (m_WiFi_WS_Ssid == "")
    {
        Serial.println("no SSID configured, skipping workstation connect");
        return false;
    }

    WiFi.disconnect();
    WiFi.setHostname(m_WiFi_Host_Name.c_str());
    WiFi.mode(WIFI_STA);
    Serial.println("Connecting as STA to WiFi: " + m_WiFi_WS_Ssid);
    WiFi.begin(wifiSiid.c_str(), WifiPwd.c_str());

    unsigned long m_intervalCurrent = millis();
    m_intervaPrevious = m_intervalCurrent;

    while (WiFi.status() != WL_CONNECTED)
    {
        m_intervalCurrent = millis();

        if (m_intervalCurrent - m_intervaPrevious >= m_interval)
        {
            ////debugE("WiFi error connecting as STA to %s", m_WiFi_WS_Ssid.c_str());
            m_intervaPrevious = millis();
            m_WiFi_ConnectedModeLast = 'f';
            return false;
        }
        delay(100);
    }
    // debugI("Wifi mode WS ipAddress %s", WiFi.localIP().toString().c_str());
    /*
        // Serial.println("WiFi connected successfully as STA, SSID: %s IP address: %s Gateway: %s Dns: %s",
        WiFi.SSID().c_str(),
            WiFi.localIP().toString().c_str(),
            WiFi.gatewayIP().toString().c_str(),
            WiFi.dnsIP().toString().c_str();
    */

    m_WiFi_ConnectedModeLast = 'w';
    IsInternetAvailableTest();
    m_intervaPrevious = millis();
    return true;
    ;
}
/// @brief  read all network config values and intialize network
/// if reset then remove overwrite network files config
/// @param pinReset true if button reset is pressed in interval
/// @param bForceReset  true force reset by sofware
/// @return
bool ClsNetworkConfig::setup(bool bResetFactoryNetwork)
{
    if (bResetFactoryNetwork)
    {
        set_config_default(bResetFactoryNetwork);
    }

    Serial.println("ClsNetworkConfig::setup()");
    configRead();
    set_config_AP(m_WiFi_AP_Ssid, m_WiFi_AP_Pwd_default);
    set_config_WS(false, m_WiFi_Host_Name, m_WiFi_WS_Ssid, m_WiFi_WS_Pwd);
    set_config_TimeRtcNtp(false, m_NtpTimeZone, m_NtpTimeZoneDayLight, m_GpsLatitude, m_GpsLongitude);
    bool b = connect_WS_Or_AP();
    // debug("from end setup");
    return b;
}
bool ClsNetworkConfig::connect_WS_Or_AP()
{
    bool bconnectWS = connectWS(m_WiFi_WS_Ssid, m_WiFi_WS_Pwd);

    ////// debugI("Trying to enable WiFi as workstation or AP");
    bconnectWS = false;

    if (connectWS(m_WiFi_WS_Ssid, m_WiFi_WS_Pwd))
    {
        m_WiFi_ConnectedModeLast = 'w';
        bconnectWS = true;
    }
    if (bconnectWS == false)
    {
        bconnectWS = connectWS(m_WiFi_WS_Ssid2, m_WiFi_WS_Pwd2);
    }

    if (bconnectWS == false)
    {
        connectAP();
        m_WiFi_ConnectedModeLast = 'a';
        m_IsInternetAvailable = false;
        bconnectWS = false;
    }
    return bconnectWS;
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
void ClsNetworkConfig::loop(bool isReset)
{
    if (isReset)

    {
        fncResetFactory();
        Serial.println("ClsNetworkConfig::loop() start");
        ESP.restart();
        return;
    }
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
            // debugW("WARNING! trying to reconnect to wifi %s", m_WiFi_WS_Ssid.c_str());
            WiFi.disconnect();
            connect_WS_Or_AP();
        }
    }
}

bool ClsNetworkConfig::configRead()
{
    set_config_default(false);
    // if not exist file then write with default value

    m_WiFi_Host_Name = ClsFileSpiffs::fileReadWithDefault(m_pathHostName, m_WiFi_Host_Name_default);
    if (m_WiFi_Host_Name == "")
    {
        m_WiFi_Host_Name = m_WiFi_Host_Name_default;
    }
    m_WiFi_WS_Ssid = ClsFileSpiffs::fileReadWithDefault(m_pathWsSsid, m_WiFi_WS_Ssid_default);

    m_WiFi_WS_Pwd = ClsFileSpiffs::fileReadWithDefault(m_pathWsPass, m_WiFi_WS_Pwd_default);

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

String ClsNetworkConfig::gethostname()
{
    
    if (m_WiFi_Host_Name == "")
    {
        m_WiFi_Host_Name = m_WiFi_Host_Name_default;
    }
    // debugI("getHostName %s",m_WiFi_Host_Name);
    return m_WiFi_Host_Name;
}
String ClsNetworkConfig::getWiFiWsSSid() { return m_WiFi_WS_Ssid; }
String ClsNetworkConfig::getWiFiWsPwd() { return m_WiFi_WS_Pwd; }
String ClsNetworkConfig::getWiFiApSsid() { return m_WiFi_AP_Ssid; }
String ClsNetworkConfig::getWiFiApPwd() { return m_WiFi_AP_Pwd; };
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
String ClsNetworkConfig::getGpsLongitude_default()
{
    char aBuffer14[14];
    dtostrf(m_GpsLongitude_default, 12, 7, aBuffer14);
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
String ClsNetworkConfig::getGpsLatitude_default()
{
    char aBuffer14[14];
    dtostrf(m_GpsLatitude_default, 12, 7, aBuffer14);
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
    fill = m_WiFi_WS_Ssid + "#" + m_WiFi_WS_Pwd + "#" + String(m_NtpTimeZone) + "#" + String(m_NtpTimeZoneDayLight) + "#" + getGpsLatitude() + "#" + getGpsLongitude() + "#" + m_WiFi_Host_Name;
    return fill;
}
String ClsNetworkConfig::getConfigDefaultFull()
{
    char buffer12_latitudeDefault[14];                               // extra for \0 or signus
    char buffer12_longitudeDefault[14];                              // extra for \0 or signus
    dtostrf(m_GpsLatitude_default, 12, 7, buffer12_latitudeDefault); // 2 position for signed and \0
    dtostrf(m_GpsLongitude_default, 12, 7, buffer12_longitudeDefault);
    String fill = "";

    fill = fill = m_WiFi_WS_Ssid_default + "#" + m_WiFi_WS_Pwd_default + "#" + String(m_NtpTimeZone_default) + "#" + String(m_NtpTimeZoneDayLight_default) + "#" + getGpsLatitude_default() + "#" + getGpsLongitude_default() + "#" + m_WiFi_Host_Name_default;
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
        Serial.println("ping 8.8.4.4 Success!!");
        test = true;
    }
    else if (Ping.ping(remote_host))
    {
        Serial.println("ping www.google.com Success!!");
        debugI("public ip: %s", GetPublicIP().c_str());
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
        Serial.println("Internet connection available");
    }
    else
    {
        // debugW("Internet connection NOT available");
    }
    return m_IsInternetAvailable;
}

void ClsNetworkConfig::debug(String from)
{
    Serial.println("===============================================================================");
    Serial.println("debug ClsWificonfig" + from);

    Serial.println("====================");
    Serial.println("Uri Host = http://" + m_WiFi_Host_Name + ".local");
    Serial.println("Uri IP   = http://" + WiFi.localIP().toString());

    Serial.println("m_WiFi_AP_Pwd=" + m_WiFi_AP_Pwd);
    Serial.println("m_WiFi_AP_Ssid=" + m_WiFi_AP_Ssid);
    Serial.println("m_WiFi_AP_Pwd=" + m_WiFi_AP_Pwd);
    Serial.println(".");
    Serial.println("m_WiFi_WS_Ssid=" + m_WiFi_WS_Ssid);
    Serial.println("m_WiFi_WS_Pwd=" + m_WiFi_WS_Pwd);
    Serial.println(".");
    Serial.println("WiFi.localIP()=" + WiFi.localIP().toString());
    Serial.println("WiFi.getMode()=" + WiFi.getMode());
    Serial.println("WiFi.getHostname()=" + String(WiFi.getHostname()));
    Serial.println("WiFi.gatewayIP()=" + WiFi.gatewayIP().toString());
    Serial.println("WiFi.getAutoReconnect()=" + String(WiFi.getAutoReconnect()));
    Serial.println("m_GpsLatitude=" + String(m_GpsLatitude));
    Serial.println("m_GpsLongitude=" + String(m_GpsLongitude));
    Serial.println(".");
    Serial.println("m_NtpTimeZone=" + String(m_NtpTimeZone));
    Serial.println("m_NtpTimeZoneDayLight=" + String(m_NtpTimeZoneDayLight));
    Serial.println("m_IsInternetAvailable=" + String(m_IsInternetAvailable));
    Serial.println("===============================================================================");
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
void ClsNetworkConfig::fncResetFactory()
{
    Serial.println("Performing factory reset 2");
    ClsFileSpiffs::fileDelete(m_pathHostName);
    ClsFileSpiffs::fileDelete(m_pathLatitude);
    ClsFileSpiffs::fileDelete(m_pathLongitude);
    ClsFileSpiffs::fileDelete(m_pathRelaysJson);
    ClsFileSpiffs::fileDelete(m_pathTimeDayLight);
    ClsFileSpiffs::fileDelete(m_pathTimeZone);
    ClsFileSpiffs::fileDelete(m_pathWsSsid);
    ClsFileSpiffs::fileDelete(m_pathWsPass);

    setup(true);
}

String ClsNetworkConfig::GetPublicIP()
{
    if ((WiFi.status() == WL_CONNECTED))
    { // Check the current connection status

        HTTPClient http;
        String status;

        http.begin("https://api.ipify.org"); // Specify the URL

        status = http.GET() > 0 ? http.getString() : "null";

        http.end(); // Free the resources
        return status;
    }
    return "No IP, not wifi connected";
}