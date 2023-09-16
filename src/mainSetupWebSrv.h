#ifndef MAINSETUPWEBSRV_H
#define MAINSETUPWEBSRV_H

#include <Arduino.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "mainDefines.h"
#include "ClsNetworkConfig.h"
#include "ClsTimeRtcNtp.h"
#include "ClsSunSetRise.h"
#include "web_html_root.h"
#include "web_html_relay_irrigation.h"
#include "web_html_relay_onoff.h"
#include "web_Html_confignet.h"
#include "web_css.h"
#include "web_js.h"
#include "web_svg.h"
#include "web_favicon.h"
#include "web_fncFillAllStatus.h"
void fncMainSetupWebSrv()
{
  g_NetWebServer.on("/js.js", HTTP_GET, [](AsyncWebServerRequest *request)
                    { 
                      digitalWrite(g_pinIntLedBlue,LOW);
                      request->send(200, "text/javascript", g_HTML_Web_JS);
                      digitalWrite(g_pinIntLedBlue,HIGH); });
  g_NetWebServer.on("/css.css", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,LOW);
                      request->send(200, "text/css", g_HTML_Web_CSS);
                      digitalWrite(g_pinIntLedBlue,HIGH); });
  g_NetWebServer.on("/svg.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,LOW);
                       request->send(200, "image/svg+xml", g_HTML_Web_SVG);
                       digitalWrite(g_pinIntLedBlue,HIGH); });

  g_NetWebServer.on("/favicon.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,LOW);
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/svg+xml", g_HTML_Web_faviconSvg);
                       digitalWrite(g_pinIntLedBlue,HIGH); });
  g_NetWebServer.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,LOW);
                       request->send(200,  "image/png", g_HTML_Web_faviconPng);
                       digitalWrite(g_pinIntLedBlue,HIGH); });

  g_NetWebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,LOW);
                        request->send(200, "text/html", g_Web_Htlm_Root);
                        digitalWrite(g_pinIntLedBlue,HIGH); });
  g_NetWebServer.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,LOW);
                        request->send(200, "text/plain", g_Web_Htlm_Root);
                        digitalWrite(g_pinIntLedBlue,HIGH); });

  g_NetWebServer.on("/relayirrigation.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,LOW);
                        request->send(200, "text/html", g_Web_Htlm_Relay_Irrigation);
                        digitalWrite(g_pinIntLedBlue,HIGH); });

  g_NetWebServer.on("/confignet.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,LOW);
                        request->send(200, "text/html", g_Web_Html_ConfigNet);
                        digitalWrite(g_pinIntLedBlue,HIGH); });

  g_NetWebServer.onNotFound([](AsyncWebServerRequest *request)
                            {
                              String body = (request->hasParam("body", true)) ? request->getParam("body", true)->value() : String();

                              // Handle not found request here...
                            });
  //------------------------------------------------------------------------

  g_NetWebServer.on("/getstatus.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                      String reply=fncFillAllStatus();
                       request->send(200, "text/html", reply); });
  //------------------------------------------------------------------------
  //------------------------------------------------------------------------
  g_NetWebServer.on("/netconfig.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/html", g_Web_Html_ConfigNet); });
  g_NetWebServer.on("/netconfigget", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/plain", g_NetworkConfig.getConfigFull()); });
  g_NetWebServer.on("/netconfiggetdefault", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/plain", g_NetworkConfig.getConfigDefaultFull()); });

  g_NetWebServer.on("/netconfigsave", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                      digitalWrite(g_pinIntLedBlue, LOW);
                      debugD("/netsaveconfig");
                      String wifiWsSsid = "";
                      String wifiWsPwd = "";
                      IPAddress wifiWsNetIp;
                      IPAddress wifiWsNetMask;
                      IPAddress wifiWsNetGat;
                      int ntpTimeZone = 2;
                      int ntpTimeZoneDayLight = 0;
                      double gpsLongitude = 0;
                      double gpsLatitude = 0;
                      String hostName = "";
                      int dhcp = 0;
                      String szMsg = "";
                      String sz = "";
                      /*
                      List of parameters on url /netsaveconfig?
                        ssid;
                        pwd
                        ip
                        mask
                        gat
                        TimeZone
                        TimeDayLight
                        lat
                        long
                        host
                        dhcp
                        */
                  

                        szMsg = szMsg + "Retrieve " ;
                        if (request->hasParam("ssid"))
                        {
                          wifiWsSsid = request->getParam("ssid")->value().c_str();
                          szMsg+=", wifiWsSsid="+wifiWsSsid;
                        }
                        if (request->hasParam("pwd"))
                        {
                          wifiWsPwd = request->getParam("pwd")->value().c_str();
                           szMsg+=", wifiWsPwd="+wifiWsPwd;
                        }

                        if (request->hasParam("ip"))
                        {
                          sz = request->getParam("ip")->value().c_str();
                          wifiWsNetIp.fromString(sz);
                           szMsg+=", wifiWsNetIp="+sz;
                        }
                        if (request->hasParam("mask"))
                        {
                          sz = request->getParam("mask")->value().c_str();
                          wifiWsNetMask.fromString(sz);
                           szMsg+=", wifiWsNetMask="+sz;
                        }
                       
                     if (request->hasParam("gat"))
                        {
                          sz = request->getParam("gat")->value().c_str();
                          wifiWsNetGat.fromString(sz);
                           szMsg+=", wifiWsNetGat="+sz;
                        }
                        if (request->hasParam("TimeZone"))
                        {
                          sz = request->getParam("TimeZone")->value().c_str();
                          ntpTimeZone = sz.toInt();
                            szMsg+=", ntpTimeZone="+sz;
                        }
                                                                  
                        if (request->hasParam("lat"))
                        {
                          sz = request->getParam("lat")->value().c_str();
                           gpsLatitude = sz.toDouble();
                               szMsg+=", gpsLatitude="+sz;
                        }
                        if (request->hasParam("long"))
                        {
                          sz = request->getParam("long")->value().c_str();
                           gpsLongitude = sz.toDouble();
                            szMsg+=", gpsLongitude="+sz;
                        }

                         if (request->hasParam("host"))
                        {
                          hostName = request->getParam("host")->value().c_str();
                             szMsg+=", hostName="+hostName;
                          
                        }
                        if (request->hasParam("dhcp"))
                        {
                          sz = request->getParam("dhcp")->value().c_str();
                          dhcp = sz.toInt();
                           szMsg+=", dhcp="+sz;
                        }
                            
                  
                 
                    

                      bool b = true;
                      if (!g_NetworkConfig.set_config_WS(true, hostName, dhcp, wifiWsSsid, wifiWsPwd, wifiWsNetIp, wifiWsNetMask, wifiWsNetGat))
                      {
                        b = false;
                      }
                      else
                      {
                        szMsg += " wifiWsSsid=" + g_NetworkConfig.getWiFiWsSSid();
                        szMsg += " wifiWsPwd=" + g_NetworkConfig.getWiFiWsPwd();
                        szMsg += " wifiWsNetIp=" + g_NetworkConfig.getWiFiWsIP();
                        szMsg += " wifiWsNetMask=" + g_NetworkConfig.getWiFiWsMask();
                        szMsg += " wifiWsNetGat=" + g_NetworkConfig.getWiFiWsGat();
                      }

                      if (!g_NetworkConfig.set_config_TimeRtcNtp(true, ntpTimeZone, ntpTimeZoneDayLight, gpsLongitude, gpsLatitude))
                      {
                        b = false;
                      }
                      else
                      {
                        szMsg += "ntpTimeZone=" + g_NetworkConfig.getNtpTimeZone();
                        szMsg += "ntpTimeZoneDayLight=" + g_NetworkConfig.getNtpTimeZoneDayLight();
                        szMsg += "GpsLongitude=" + g_NetworkConfig.getGpsLongitude();
                        szMsg += "GpsLatitude=" + g_NetworkConfig.getGpsLatitude();
                      }
                      if (b)
                      {
                        szMsg += "<br/>Saved";
                      }
                      else
                      {
                        szMsg += "<br/>ERROR: Not saved";
                      }

                      szMsg + "<br/><b>The changes will be applied on next restart: You can click on button abobe this form</b>";
                      request->send(200, "text/html", "message received: " + szMsg);
                      digitalWrite(g_pinIntLedBlue, HIGH); });

  //------------------------------------------------------------------------
  g_NetWebServer.on("/relayonof.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,LOW);
                        request->send(200, "text/html", g_Web_Htlm_Relay_OnOff);
                        digitalWrite(g_pinIntLedBlue,HIGH); });
  g_NetWebServer.on("/relayonoffset", HTTP_GET, [](AsyncWebServerRequest *request)
                    {

       digitalWrite(g_pinIntLedBlue, LOW);

       debugD("/relayonoffset %s", request->url().c_str());
       int paramsNr = request->params();

      AsyncWebParameter *pIdRelay = request->getParam("idrelay");
      AsyncWebParameter *pOnOff = request->getParam("onoff");

      String pIdRelayName = pIdRelay->name();
      int iIdRelay = pIdRelay->value().toInt();
      int iOnOff = pOnOff->value().toInt();

      debugD("onoff received idRelay=%d onoff=%d", iIdRelay, iOnOff);

      if (iOnOff == 0)
      {
        g_Relays.m_RelaysOnOff[iIdRelay].setClose();
      }
      if (iOnOff == 1)
      {
        g_Relays.m_RelaysOnOff[iIdRelay].setOpen();
      }

      request->send(200, "text/plain", "message receive "+  request->url() +" pin="+String(g_Relays.m_RelaysOnOff[iIdRelay].getPin()));
      digitalWrite(g_pinIntLedBlue, HIGH); });

  //------------------------------------------------------------------------
  g_NetWebServer.onNotFound([](AsyncWebServerRequest *request)
                            { request->send(404, "text/plain", "The content you are looking for was not found."); });
  //------------------------------------------------------------------------

  debugI("starting Web Server");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "content-type");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  g_NetWebServer.begin();
  digitalWrite(g_pinIntLedBlue, LOW);
}

#endif