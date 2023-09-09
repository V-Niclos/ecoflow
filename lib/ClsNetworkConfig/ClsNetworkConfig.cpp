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
    m_pinReset = -1;
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
    fncFileWriteValue(SPIFFS, m_pathSsid, m_WiFI_WS_Ssid.c_str());
    fncFileWriteValue(SPIFFS, m_pathPass, m_WiFI_WS_Pwd.c_str());

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
    // Save config
    fncFileWriteValue(SPIFFS, m_pathSsid, m_WiFI_WS_Ssid.c_str());
    fncFileWriteValue(SPIFFS, m_pathPass, m_WiFI_WS_Pwd.c_str());
    fncFileWriteValue(SPIFFS, m_pathIP, m_WiFI_WS_IP.toString().c_str());
    fncFileWriteValue(SPIFFS, m_pathMask, m_WiFI_WS_Mask.toString().c_str());
    fncFileWriteValue(SPIFFS, m_pathGateway, m_WiFI_WS_Gateway.toString().c_str());
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

    fncFileWriteValue(SPIFFS, m_pathTimeZone, String(m_NtpTimeZone).c_str());
    fncFileWriteValue(SPIFFS, m_pathTimeDayLight, String(m_NtpTimeZoneDayLight).c_str());
    // fncFileWriteValue(SPIFFS, m_pathLatitude,  std::to_string(m_GpsLatitude));

    char cLatitude[14];
    char cLongitude[14];
    dtostrf(m_GpsLatitude, 12, 7, cLatitude);
    dtostrf(m_GpsLongitude, 12, 7, cLongitude);
    fncFileWriteValue(SPIFFS, m_pathLatitude, cLatitude);
    fncFileWriteValue(SPIFFS, m_pathLongitude, cLongitude);

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
        Serial.println("STA Failed to configure");
    }
    WiFi.softAP(m_WiFI_AP_Ssid.c_str(), m_WiFI_AP_Pwd.c_str());
    Serial.println("Wifi connected as ");
    Serial.printf("[WIFI] Acces Point Mode, SSID: %s, IP address: %s\n", m_WiFI_AP_Ssid.c_str(), WiFi.softAPIP().toString().c_str());
    m_WiFi_ConnectedModeLast = 'a';
    return true;
}

//------------------------------------
bool ClsNetworkConfig::connectWS()
{
    Serial.println("ClsNetworkConfig::connectWS()");
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
    return true;
    ;
}
bool ClsNetworkConfig::setup(int8_t pinReset, bool bForceReset)
{
    m_pinReset = pinReset;
    // if is set pin reset read
    if (m_pinReset > 0 && digitalRead(m_pinReset) == HIGH)
    {
        bForceReset = true;
    }
    // reset factory
    if (bForceReset)
    {
        set_config_default();
        set_config_AP(m_WiFI_AP_Ssid, m_WiFI_AP_Pwd);

        set_config_WS(m_WiFI_WS_Ssid, m_WiFI_WS_Pwd, m_WiFI_WS_IP, m_WiFI_WS_Mask, m_WiFI_WS_Gateway_default);
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
    if (m_intervaPrevious < m_intervalCurrent)
    {
        m_intervaPrevious = 0;
    }
    if (m_intervalCurrent - m_intervaPrevious >= m_interval)
    {
        Serial.println("WARNING! traying to reconnect to wifi " + m_WiFI_WS_Ssid);
        if (m_WiFi_ConnectedModeLast == 'a')
        {
            WiFi.disconnect();
            connect_WS_Or_AP();
            m_intervaPrevious = m_intervalCurrent;
        }
    }
}
bool ClsNetworkConfig::fncFileExist(String filePaht)
{
    File file = SPIFFS.open(filePaht, FILE_READ);

    if (!file)
    {
        return false;
    }
    file.close();
    return true;
}

bool ClsNetworkConfig::configRead()
{
    Serial.print("-------------------------------------ClsNetworkConfig::configRead() start:");
    fncFileSpiffsInit();
    set_config_default();
    if (fncFileExist(m_pathSsid))
    {
        m_WiFI_WS_Ssid = fncFileReadValue(SPIFFS, m_pathSsid);
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathSsid, m_WiFI_WS_Ssid.c_str());
    }
    if (fncFileExist(m_pathPass))
    {
        m_WiFI_WS_Pwd = fncFileReadValue(SPIFFS, m_pathPass);
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathPass, m_WiFI_WS_Pwd.c_str());
    }

    if (fncFileExist(m_pathIP))
    {
        m_WiFI_WS_IP.fromString(fncFileReadValue(SPIFFS, m_pathIP));
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathIP, m_WiFI_WS_IP.toString().c_str());
    }
    if (fncFileExist(m_pathMask))
    {
        m_WiFI_WS_Mask.fromString(fncFileReadValue(SPIFFS, m_pathMask));
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathMask, m_WiFI_WS_Mask.toString().c_str());
    }
    if (fncFileExist(m_pathGateway))
    {
        m_WiFI_WS_Gateway.fromString(fncFileReadValue(SPIFFS, m_pathGateway));
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathGateway, m_WiFI_WS_Gateway.toString().c_str());
    }
    if (fncFileExist(m_pathDns1))
    {
        m_WiFI_WS_DNS1.fromString(fncFileReadValue(SPIFFS, m_pathDns1));
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathDns1, m_WiFI_WS_DNS1_default.toString().c_str());
    }
    if (fncFileExist(m_pathDns2))
    {
        m_WiFI_WS_DNS2.fromString(fncFileReadValue(SPIFFS, m_pathDns2));
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathDns2, m_WiFI_WS_DNS2_default.toString().c_str());
    }
    if (fncFileExist(m_pathTimeZone))
    {
        m_NtpTimeZone = fncFileReadValue(SPIFFS, m_pathTimeZone).toInt();
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathTimeZone, String(m_NtpTimeZone).c_str());
    }
    if (fncFileExist(m_pathTimeDayLight))
    {
        m_NtpTimeZoneDayLight = fncFileReadValue(SPIFFS, m_pathTimeDayLight).toInt();
    }
    else
    {
        fncFileWriteValue(SPIFFS, m_pathTimeDayLight, String(m_NtpTimeZoneDayLight).c_str());
    }

    if (fncFileExist(m_pathLatitude))
    {
        m_GpsLatitude = fncFileReadValueDouble(SPIFFS, m_pathLatitude);
    }
    else
    {
        char cLatitude[14];
        dtostrf(m_GpsLatitude, 12, 7, cLatitude);
        fncFileWriteValue(SPIFFS, m_pathLatitude, cLatitude);
    }
    if (fncFileExist(m_pathLongitude))
    {
        m_GpsLatitude = fncFileReadValueDouble(SPIFFS, m_pathLongitude);
    }
    else
    {
        char cLongitude[14];
        dtostrf(m_GpsLongitude, 12, 7, cLongitude);
        fncFileWriteValue(SPIFFS, m_pathLongitude, cLongitude);
    }

    //====================================================
    //====================================================
    //====================================================
    return true;
}
//===========================================================
//===========================================================
//===========================================================
bool ClsNetworkConfig::fncFileSpiffsInit()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return false;
    }
    Serial.println("SPIFFS mounted successfully");
    return true;
}
double ClsNetworkConfig::fncFileReadValueDouble(fs::FS &fs, const char *path)
{
    // Serial.println("=================== fncFileReadValueDouble ======================");
    // Serial.printf("\n\rReading file: %s value: ", path);
    double dFileContent = 0;
    String sFileContent = "";
    char *tok;
    File file = fs.open(path);
    if (!file || file.isDirectory())
    {
        // Serial.println("- failed to open file for reading");
        return 0;
    }

    while (file.available())
    {
        sFileContent = String(file.readStringUntil('\n'));

        break;
    }
    dFileContent = strtod(sFileContent.c_str(), &tok);
    // Serial.print(sFileContent);
    // Serial.print(" tranformado ");
    // Serial.println(dFileContent, 9);

    // Serial.println("=================== fncFileReadValueDouble END======================");
    return dFileContent;
}
String ClsNetworkConfig::fncFileReadValue(fs::FS &fs, const char *path)
{

    // //Serial.println("=================== fncFileReadValue ==========================");
    Serial.printf("\n\rReading file: %s value: ", path);

    File file = fs.open(path);
    if (!file || file.isDirectory())
    {
        // Serial.println("- failed to open file for reading");
        return String();
    }

    String fileContent;

    while (file.available())
    {
        fileContent = String(file.readStringUntil('\n'));

        break;
    }
    Serial.println(fileContent);
    //  //Serial.println("=================== fncFileReadValue END======================");
    return fileContent;
}
//===========================================================
//===========================================================
//===========================================================
void ClsNetworkConfig::fncFileWriteValue(fs::FS &fs, const char *path, const char *value)
{
    // Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        // Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(value))
    {
        Serial.println("--------------------------------write file: start ");
        Serial.print("write file: ");
        Serial.print(path);
        Serial.println(" value= ");
        Serial.println(value);
    }
    else
    {
        // Serial.println("- frite failed");
    }
    file.flush();
    file.close();
    Serial.print("--------------------------------write file: end ");
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

 int ClsNetworkConfig::get_NtpTimeZone(){return m_NtpTimeZone;}
 int ClsNetworkConfig::get_NtpTimeZoneDayLight (){return m_NtpTimeZoneDayLight;}
 double ClsNetworkConfig::get_GpsLatitude() {return m_GpsLatitude;}
 double ClsNetworkConfig::get_GpsLongitude(){return m_GpsLongitude;}

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
    if(m_IsInternetAvailable)
    {
        Serial.println(" Succes!");
    }else { Serial.println(" fail!");}
    return m_IsInternetAvailable;
}

void ClsNetworkConfig::debug(String from){
    Serial.println("====================");
    Serial.println("debug ClsWificonfig" + from);

    Serial.println("====================");
    Serial.println(".");
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