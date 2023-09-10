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
String fncFillAllStatus();
void fncMainSetupWebSrv()
{
  g_NetWebServer.on("/js.js", HTTP_GET, [](AsyncWebServerRequest *request)
                    { 
                      digitalWrite(g_pinIntLedBlue,HIGH);  
                      request->send(200, "text/javascript", g_HTML_Web_JS);  
                      digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/css.css", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                      request->send(200, "text/css", g_HTML_Web_CSS);  
                      digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/svg.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       request->send(200, "image/svg+xml", g_HTML_Web_SVG);  
                       digitalWrite(g_pinIntLedBlue,LOW); });

  g_NetWebServer.on("/favicon.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/svg+xml", g_HTML_Web_faviconSvg);  
                       digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       request->send(200,  "image/png", g_HTML_Web_faviconPng);  
                       digitalWrite(g_pinIntLedBlue,LOW); });

  g_NetWebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,HIGH);
                        request->send(200, "text/html", g_Web_Htlm_Root);
                        digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,HIGH);  
                        request->send(200, "text/plain", g_Web_Htlm_Root);
                        digitalWrite(g_pinIntLedBlue,LOW); });

  g_NetWebServer.on("/relayirrigation.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,HIGH);  
                        request->send(200, "text/html", g_Web_Htlm_Relay_Irrigation);
                        digitalWrite(g_pinIntLedBlue,LOW); });

  g_NetWebServer.on("/confignet.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,HIGH);  
                        request->send(200, "text/html", g_Web_Html_ConfigNet);
                        digitalWrite(g_pinIntLedBlue,LOW); });

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
  g_NetWebServer.on("/netConfigfetdefault", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/plain", g_NetworkConfig.getConfigDefaultFull()); });

  g_NetWebServer.on("/netsaveconfig", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                      digitalWrite(2, HIGH);
                      // Serial.println("/setConfigSave-----------------------------");

                      String wifiWsSsid = "";
                      String wifiWsPwd = "";
                      IPAddress wifiWsNetIp;
                      IPAddress wifiWsNetMask;
                      IPAddress wifiWsNetGat;
                      int ntpTimeZone = 2;
                      int ntpTimeZoneDayLight = 0;
                      double gpsLongitude = 0;
                      double gpsLatitude = 0;
                      String szMsg = "";
                      String sz = "";
                      int paramsNr = request->params();
                      // Serial.println(paramsNr);

                      for (int i = 0; i < paramsNr; i++)
                      {

                        AsyncWebParameter *p = request->getParam(i);
                        // Serial.print("p->name(): ");
                        // Serial.print(p->name());
                        // Serial.print("p->value(): ");
                        // Serial.print(p->value());
                        // Serial.print(" Convert to: ");
                        szMsg = szMsg + p->name() + "=" + p->value() + ", ";
                        if (i == 0)
                        {
                          wifiWsSsid = p->value().c_str();
                          // Serial.println(wifiWsSsid);
                        }
                        if (i == 1)
                        {
                          wifiWsPwd = p->value().c_str();
                          // Serial.println(wifiWsSsid);
                        }
                        if (i == 2)
                        {
                          sz = p->value().c_str();
                          wifiWsNetIp.fromString(sz);
                          // Serial.println(wifiWsNetIp.toString());
                        }
                        if (i == 3)
                        {
                          sz = p->value().c_str();
                          wifiWsNetMask.fromString(sz);
                          // Serial.println(wifiWsNetMask.toString());
                        }
                        if (i == 4)
                        {
                          sz = p->value().c_str();
                          wifiWsNetGat.fromString(sz);
                          // Serial.println(wifiWsNetGat.toString());
                        }
                        if (i == 5)
                        {
                          sz = p->value().c_str();
                          ntpTimeZone = sz.toInt();
                          // Serial.println(ntpTimeZone);
                        }
                        if (i == 6)
                        {
                          sz = p->value().c_str();
                          ntpTimeZoneDayLight = sz.toInt();
                          // Serial.println(ntpTimeZoneDayLight);
                        }
                        if (i == 7)
                        {
                          sz = p->value().c_str();
                          gpsLongitude = sz.toDouble();

                          // Serial.print("  gpsLongitude converted to double ");
                          // Serial.println(gpsLongitude, 9);
                        }
                        if (i == 8)
                        {
                          sz = p->value().c_str();
                          gpsLatitude = sz.toDouble();
                          // Serial.print(" sz= ");
                          // Serial.print(sz);
                          // Serial.print("  gpsLatitude converted to double ");
                          // Serial.println(gpsLatitude, 9);
                        }
                      }

                      bool b = true;
                      if (!g_NetworkConfig.set_config_WS(wifiWsSsid, wifiWsPwd, wifiWsNetIp, wifiWsNetMask, wifiWsNetGat))
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

                      if (!g_NetworkConfig.set_config_TimeRtcNtp(ntpTimeZone, ntpTimeZoneDayLight, gpsLongitude, gpsLatitude))
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
                      digitalWrite(2, LOW);

                      // ESP.restart();
                    });

  //------------------------------------------------------------------------
  g_NetWebServer.on("/relayonof.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        //Serial.println("Index");
                        digitalWrite(g_pinIntLedBlue,HIGH);  
                        request->send(200, "text/html", g_Web_Htlm_Relay_OnOff);
                        digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/relayonoffset", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                          // Serial.println("Index");
    digitalWrite(g_pinIntLedBlue, HIGH);
     
       Serial.println ("/relayonoffset "+request->url());
int paramsNr = request->params();
      for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        Serial.println("------");
    }
      AsyncWebParameter *pIdRelay = request->getParam("idrelay");
      AsyncWebParameter *pOnOff = request->getParam("onoff");
  
      String pIdRelayName = pIdRelay->name();
      int iIdRelay = pIdRelay->value().toInt();
      int iOnOff = pOnOff->value().toInt();
      Serial.println("onoff recived");
      Serial.print("idrelay=");
      Serial.println(iIdRelay);
      Serial.print("OnOff=");
      Serial.println(iOnOff);
      if (iOnOff == 0)
      {
        g_Relays.m_RelaysOnOff[iIdRelay].setClose();
      }
      if (iOnOff == 1)
      {
        g_Relays.m_RelaysOnOff[iIdRelay].setOpen();
      }
     
         request->send(200, "text/plain", "message receive "+  request->url() +" pin="+String(g_Relays.m_RelaysOnOff[iIdRelay].getPin()));
      digitalWrite(g_pinIntLedBlue, LOW); });

  //------------------------------------------------------------------------
  g_NetWebServer.onNotFound([](AsyncWebServerRequest *request)
                            { request->send(404, "text/plain", "The content you are looking for was not found."); });
  //------------------------------------------------------------------------

  Serial.println("g_NetWebServer.begin();");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "content-type");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  g_NetWebServer.begin();
  digitalWrite(2, LOW);
}
String fncFillAllStatus()
{
  return "hola mundo";
  /*
  String htmlResult = "";
  // htmlResult += "<br/>Date " + g_TimeRtcNtp.TimeLocalHHMM() + " " + g_TimeRtcNtp.DateLocalYYYYMMDD();
  // htmlResult += "<br/>Date " + g_TimeRtcNtp.NowString();
  htmlResult += g_Relays.m_RelaysIrrigation[0].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysIrrigation[1].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysOnOff[0].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysOnOff[1].getHtmlStatus();
  htmlResult += g_Relays.m_RelaysOnOff[2].getHtmlStatus();
  Serial.println(htmlResult);
  return htmlResult;
  */
}
#endif