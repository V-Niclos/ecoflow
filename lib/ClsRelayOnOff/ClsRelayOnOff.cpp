#include "ClsRelayOnOff.h"

ClsRelayOnOff::ClsRelayOnOff(/* args */)
{
}

ClsRelayOnOff::~ClsRelayOnOff()
{
}
uint8_t ClsRelayOnOff::getPin() { return m_RelayPin; }
void ClsRelayOnOff::setup( uint8_t relayId,  uint8_t relayPin,   String relayName ,eOPENCLOSE eOpenClose)
{
   
    m_RelayId = relayId;
    m_RelayPin = relayPin;
    m_RelayName = relayName;
    Serial.printf(" ClsRelayOnOff::setup Relay id %u, relayPin %u, relayName %d", relayId, relayPin, relayName);
    pinMode(m_RelayPin, OUTPUT);
    
    digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
}
// TODO
void ClsRelayOnOff::loop(bool isReset)
{
    if (isReset)
    {
        fncResetFactory();
        return;
    }
}
void ClsRelayOnOff::setOpen()
{

    debugI("ClsRelayOnOff::setOpen() Id relay %u  Name: %s Pin: %u", m_RelayId, m_RelayName, m_RelayPin);
    digitalWrite(m_RelayPin, eOPENCLOSE_OPEN);
}
void ClsRelayOnOff::setClose()
{
    debugI("ClsRelayOnOff::setOpen() Id relay %u  Name: %s Pin: %u", m_RelayId, m_RelayName, m_RelayPin);
    digitalWrite(m_RelayPin, eOPENCLOSE_CLOSE);
}
String ClsRelayOnOff::getJsonFromValues()
{
    String result = "";
    result = "{\"Lines\": [";
    for (uint8_t id = 0; id < 3; id++)
    {

        result += "{";
        result += ("\"RelayId\":\"" + String(m_RelayId) + "\", ");
        result += ("\"RelayPin\":\"" + String(m_RelayPin) + "\", ");
        result += ("\"RelayName\":\"" + String(m_RelayName) + "\", ");

        result += ("\"PrgIsOpen\":\"" + String(getIsOpen()) + "\"");
        result += "}";
    }
    result += "]}";

    return result;
}

uint8_t ClsRelayOnOff::getIsOpen()
{
    if (digitalRead(m_RelayPin) == eOPENCLOSE_OPEN)
    {
        return 1;
    }

    return 0;
}

String ClsRelayOnOff::getHtmlStatus()
{

    String resultHtml = "<hr/><h5>Relays type on off</h5><p>";
    resultHtml += "<b>" + String(m_RelayId) + " ";
    resultHtml += m_RelayName + " </b>";
    if (getIsOpen())
    {
        resultHtml += "<span class=\"led green\"></span>";
    }
    else
    {
        resultHtml += "<span class=\"led red\"></span>";
    }

    resultHtml += "<p>";
    return resultHtml;
}
void ClsRelayOnOff::fncResetFactory() {}