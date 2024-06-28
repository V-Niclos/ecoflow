#ifndef MAINSETUPWEBSRV_H
#define MAINSETUPWEBSRV_H
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "mainSetupOta.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "mainDefines.h"
#include "mainSetupOta.h"

#include "mainFlowSensor.h"
#include "ClsNetworkConfig.h"
#include "ClsTimeRtcNtp.h"
#include "ClsSunset.h"
#include "web_html_root.h"
#include "web_html_irrigation_auto.h"
#include "web_html_irrigation_manual.h"

#include "web_Html_confignet.h"
#include "web_css.h"
#include "web_js.h"

#include "web_svg.h"
#include "web_favicon.h"
#include "web_htm_getrelaystatus.h"
/*
{
   "relayIrrigation":[
      {
         "relayId":"0",
         "relayName":"zona jardin"
      }
   ],
   "prg":[
      {
         "id":"0",
         "name":"noches",
         "minutes":"13",
         "mode":"1",
         "onOff":"1",
         "startHHMM":"12:14",
         "intervalDays":"2"
      }
   ]
}
*/
void fncRelayIrrigationSet(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  digitalWrite(g_pinLedFlash, HIGH_INT_LED);

  String sJson = "";
  for (size_t i = 0; i < len; i++)
  {
    sJson.concat((char)data[i]);
  }
  // // debugI("fncRelayIrrigationSet   sJson= %s", sJson);
  //  StaticJsonDocument<1024> jsondoc;
  JsonDocument jsondoc;
  //  JsonDocument jsondoc;
  DeserializationError error = deserializeJson(jsondoc, sJson.c_str());
  if (error)
  {
    debugE("ERROR fncRelayIrrigationSet deserializeJson =  %s", error.c_str());
    debugE("sJson= %s", sJson.c_str());
    request->send(400);
    return;
  }

  JsonObject jsObject = jsondoc.as<JsonObject>();

  // debugI(" fncRelayIrrigationSet recived values");
  // debugI("m_RelayId %s", jsondoc["m_RelayId"].as<String>().c_str());
  // debugI("m_RelayName %s", jsondoc["m_RelayName"].as<String>().c_str());
  // debugI("m_PrgAuto_Description %s", jsondoc["m_PrgAuto_Description"].as<String>().c_str());
  // debugI("m_PrgAuto_IsActive %s", jsondoc["m_PrgAuto_IsActive"].as<String>().c_str());
  // debugI("m_PrgAuto_StartHHMM %s", jsondoc["m_PrgAuto_StartHHMM"].as<String>().c_str());

  int relayId = jsondoc["m_RelayId"];

  g_Relays.saveIrrigation(relayId, sJson);

  String reply = g_Relays.m_RelaysIrrigationPrg[relayId].getJsonFromValues();
  request->send(200, "application/json", reply);

  digitalWrite(g_pinLedFlash, LOW_INT_LED);

  return;
}
void fncMainSetupWebSrv()
{
  digitalWrite(g_pinLedFlash, HIGH_INT_LED);
  g_NetWebServer.on("/js.js", HTTP_GET, [](AsyncWebServerRequest *request)
                    { 
                      digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                      request->send(200, "text/javascript", g_HTML_Web_JS);
                      digitalWrite(g_pinLedFlash,LOW_INT_LED); });

  g_NetWebServer.on("/css.css", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                      request->send(200, "text/css", g_HTML_Web_CSS);
                      digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  g_NetWebServer.on("/svg.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                       request->send(200, "image/svg+xml", g_HTML_Web_SVG);
                       digitalWrite(g_pinLedFlash,LOW_INT_LED); });

  g_NetWebServer.on("/favicon.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/svg+xml", g_HTML_Web_faviconSvg);
                       digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  g_NetWebServer.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                       request->send(200,  "image/png", g_HTML_Web_faviconPng);
                       digitalWrite(g_pinLedFlash,LOW_INT_LED); });

  g_NetWebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                 
                        request->send(200, "text/html", g_Web_Htlm_Root);
                        digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  g_NetWebServer.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                        request->send(200, "text/plain", g_Web_Htlm_Root);
                        digitalWrite(g_pinLedFlash,LOW_INT_LED); });

  g_NetWebServer.on("/irrigationauto.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                           digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                        request->send(200, "text/html", g_Web_Htlm_Irrigation_Auto);
                           digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  g_NetWebServer.on("/relayirrigationset2", HTTP_POST, [](AsyncWebServerRequest *request)
                    {
                           digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                           String jsonData="";
     int paramsNr = request->params(); // number of params (e.g., 1)
     // debugI("parmsters count=%u  ",paramsNr);
     for (int i=0;i<paramsNr;i++)
     {
      AsyncWebParameter * j = request->getParam(i);
      String value=String(j->value());
      // debugI("parmeter=%u value=%s",i,value.c_str() );
     }

    
    AsyncWebParameter * j = request->getParam(0); // 1st parameter
   // Serial.print("Size: ");
   // Serial.print(j->value());                     // value ^
   // Serial.println();

    if (request->hasParam("data", true))
    {
      jsonData = request->getParam("data", true)->value();
      // debugI("server recived jsondata = %s", jsonData.c_str());
      request->send(200, "text/plain", "Server recived jsondata, POST: " + jsonData);
    }
    else
    {
        request->send(200, "text/plain", "Server NOT recived jsondata, POST: jsonData " );
    }
    
                        request->send(200, "text/html", g_Web_Htlm_Irrigation_Auto);
                           digitalWrite(g_pinLedFlash,LOW_INT_LED); });

  g_NetWebServer.on("/relayirrigationset", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, fncRelayIrrigationSet);

  g_NetWebServer.on("/irrigationautoget", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                       uint8_t idRelay=0;
                     
                         if (request->hasParam("idRelay"))
                        {
                          idRelay= request->getParam("idRelay")->value().toInt();
                        }
                          String reply=g_Relays.m_RelaysIrrigationPrg[idRelay].getJsonFromValues();
                          //// debugI("Send %s",reply.c_str());
                        request->send(200, "application/json",reply);
                       
                         digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  //   pUrl = "/relayirrigationget?idRelay=" + relayId+"&json="+ fncGetRelayJsonFromScreen();

  g_NetWebServer.on("/confignet.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                        request->send(200, "text/html", g_Web_Html_ConfigNet);
                        digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  //------------------------------------------------------------------------
  g_NetWebServer.on("/getstatus", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                    digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                    AsyncWebParameter *pIdRelay = request->getParam("idRelay");
                    int iIdRelay = pIdRelay->value().toInt();
                    String reply=fncHtmlGetRelayStatus(iIdRelay);
                    request->send(200, "text/html", reply);
                    digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  //------------------------------------------------------------------------
  g_NetWebServer.on("/netconfig.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {  digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                      request->send(200, "text/html", g_Web_Html_ConfigNet); });
  g_NetWebServer.on("/netconfigget", HTTP_GET, [](AsyncWebServerRequest *request)
                    {  digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                      request->send(200, "text/plain", g_NetworkConfig.getConfigFull()); 
                      digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  g_NetWebServer.on("/netconfiggetdefault", HTTP_GET, [](AsyncWebServerRequest *request)
                    {  digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                      request->send(200, "text/plain", g_NetworkConfig.getConfigDefaultFull());
                      digitalWrite(g_pinLedFlash,LOW_INT_LED); });

  g_NetWebServer.on("/netconfigsave", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                      digitalWrite(g_pinLedFlash, HIGH_INT_LED);
                      //debugD("/netsaveconfig");
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
                          sz.replace(',','.');
                           gpsLatitude = sz.toDouble();
                               szMsg+=", gpsLatitude="+sz;
                        }
                        if (request->hasParam("long"))
                        {
                          sz = request->getParam("long")->value().c_str();
                          sz.replace("," , ".");
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
                      if (!g_NetworkConfig.set_config_WS(true, hostName,  wifiWsSsid, wifiWsPwd))
                      {
                        b = false;
                      }
                      else
                      {
                        szMsg += " wifiWsSsid=" + g_NetworkConfig.getWiFiWsSSid();
                        szMsg += " wifiWsPwd=" + g_NetworkConfig.getWiFiWsPwd();
                 
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
                      digitalWrite(g_pinLedFlash, LOW_INT_LED); });

  //---------------------------------------------------------------------------
  //
  g_NetWebServer.on("/irrigationmanualset", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
    digitalWrite(g_pinLedFlash, HIGH_INT_LED);
    debugD("/relayManualfset %s", request->url().c_str());
    int paramsNr = request->params();

    AsyncWebParameter *pIdRelay = request->getParam("idrelay");
    AsyncWebParameter *pMinutes = request->getParam("minutes");

    String pIdRelayName = pIdRelay->name();
    int iIdRelay = pIdRelay->value().toInt();
    int iMinutes = pMinutes->value().toInt();
    // debugI("split uri relayManualfset received idRelay=%d iMinutes=%d", iIdRelay, iMinutes);
     DateTime now = g_TimeRtcNtp.nowDateTime_lastRead();
    g_Relays.m_RelaysIrrigationPrg[iIdRelay].setupPrg_Manual(now,iMinutes);
  
    
      request->send(200, "text/plain", "message received " + request->url()+ "//idrelay="+ iIdRelay+ "&iMinutes=" + String(iMinutes));
      digitalWrite(g_pinLedFlash, LOW_INT_LED); });

  //------------------------------------------------------------------------
  g_NetWebServer.on("/irrigationmanual.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                        request->send(200, "text/html", g_Web_Htlm_Water_Manual);
                        digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  g_NetWebServer.on("/flow", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinLedFlash,HIGH_INT_LED);
                        request->send(200, "text/plain", fncFlow_TextValues());
                        digitalWrite(g_pinLedFlash,LOW_INT_LED); });
  //------------------------------------------------------------------------
  g_NetWebServer.onNotFound([](AsyncWebServerRequest *request)
                            { 
                              digitalWrite(g_pinLedFlash, HIGH_INT_LED);
                              request->send(404, "text/plain", "The content you are looking for was not found."); 
                             digitalWrite(g_pinLedFlash, LOW_INT_LED); });
  //------------------------------------------------------------------------

  // // debugI("starting Web Server");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "content-type");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  //https://docs.elegantota.pro/async-mode/


  g_NetWebServer.begin();
  digitalWrite(g_pinLedFlash, LOW_INT_LED);
}

#endif