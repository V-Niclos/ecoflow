#ifndef CLSTHINGSPEAK_H
#define CLSTHINGSPEAK_H
#include <arduino.h>
#include <ThingSpeak.h>
#include <RemoteDebug.h>
#include "RTClib.h"
#include <WiFi.h>
#include "secret.h"
extern RemoteDebug Debug;
/*
Fields sended
litres_1
litres_2
flow_1
flow_2
 */
class ClsThingSpeak
{
private:
    unsigned long m_ThingSpeak_channnelID = THINSPEAK_CHANEL_id;
    const char *m_ThingSpeak_APIKey_Write = THINSPEAK_API_WRITE;
    const char *m_ThingSpeak_APIKey_Read = THINSPEAK_API_READ;
    WiFiClient m_WifiClient;
    bool m_flow_NeedSend=false;
    DateTime m_flow_LastDT = time(0);
    uint32_t m_flow_Litres_1 = 0;
    uint32_t m_flow_Litres_2 = 0;
    uint32_t m_flow_LitresMinute_1 = 0;
    uint32_t m_flow_LitresMinute_2 = 0;
    uint64_t m_IntervalPrevious=0;
    uint64_t m_IntervalSwitch=30000;
 void sendTo_ThingSpeak();
public:
    ClsThingSpeak(/* args */);
    ~ClsThingSpeak();
    void setup();
    void loop();
    void setData(DateTime flow_LastDT, uint32_t m_flow_Litres_1, uint32_t m_flow_Litres_2, uint32_t m_flow_LitresMinute_1, uint32_t m_flow_LitresMinute_2);
   
};
#endif