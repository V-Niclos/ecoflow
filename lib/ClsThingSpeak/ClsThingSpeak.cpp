#include "ClsThingSpeak.h"

ClsThingSpeak::ClsThingSpeak(/* args */)
{
}

ClsThingSpeak::~ClsThingSpeak()
{
}
void ClsThingSpeak::setup()
{
    ThingSpeak.begin(m_WifiClient);
    m_flow_NeedSend = false;
}
void ClsThingSpeak::loop()
{
    if (!m_flow_NeedSend)
    {
        return;
    }
    if (millis() - m_IntervalPrevious < m_IntervalSwitch)
    {
        return;
    }
    sendTo_ThingSpeak();
}
void ClsThingSpeak::setData(DateTime flow_LastDT, uint32_t flow_Litres_1, uint32_t flow_Litres_2, uint32_t flow_LitresMinute_1, uint32_t flow_LitresMinute_2)
{
    m_flow_NeedSend = true;
    m_flow_LastDT = flow_LastDT;
    m_flow_Litres_1 = flow_Litres_1;
    m_flow_Litres_2 = flow_Litres_2;
    m_flow_LitresMinute_1 = flow_LitresMinute_1;
    m_flow_LitresMinute_2 = flow_LitresMinute_2;
}
void ClsThingSpeak::sendTo_ThingSpeak()
{
    // https://github.com/mathworks/thingspeak-arduino/blob/master/examples/ESP32/WriteMultipleFields/WriteMultipleFields.ino
    char dateFormat[] = "YYYY-MM-DD-hh:mm:ss";
    ;

    // 200 0k
    if (!WiFi.status() != WL_CONNECTED)
    {
        ThingSpeak.setStatus(m_flow_LastDT.toString(dateFormat));
        ThingSpeak.setField(1, String(m_flow_Litres_1));
        ThingSpeak.setField(2, String(m_flow_Litres_2));
        ThingSpeak.setField(3, String(m_flow_LitresMinute_1));
        ThingSpeak.setField(4, String(m_flow_LitresMinute_2));
        int iResponse = ThingSpeak.writeFields(m_ThingSpeak_channnelID, m_ThingSpeak_APIKey_Write);
        // debugI("ThingSpeak.writeFields response=%d", iResponse);
        String Message = "";
        switch (iResponse)
        {
        case 200:
            m_flow_NeedSend = false;
            Message = "200	OK / Success";
            break;
        case 404:
            Message = "404	Incorrect API key (or invalid ThingSpeak server address)";
            break;
        case -101:
            Message = "-101	Value is out of range or string is too long (> 255 characters)";
            break;
        case -201:
            Message = "-210	Invalid field number specified";
            break;
        case -210:
            Message = "-210	setField() was not called before writeFields()";
            break;
        case -301:
            Message = "-301	Failed to connect to ThingSpeak";
            break;
        case -302:
            Message = "-302	Unexpected failure during write to ThingSpeak";
            break;
        case -303:

            Message = "-303	Unable to parse response";
            break;
        case -304:

            Message = "-304	Timeout waiting for server to respond";
            break;
        case -401:

            Message = "-401	Point was not inserted (most probable cause is the rate limit of once every 15 seconds)";
            break;
        case -0:

            Message = " 0	Other error";
            break;
        default:
           
            break;
        }
        // debugI("ThingSpeak send data: %s", Message.c_str());
        ThingSpeak.getLastReadStatus();
      
    }
}
  
