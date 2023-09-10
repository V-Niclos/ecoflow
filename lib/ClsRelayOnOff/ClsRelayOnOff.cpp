#include "ClsRelayOnOff.h"

ClsRelayOnOff::ClsRelayOnOff(/* args */)
{
}

ClsRelayOnOff::~ClsRelayOnOff()
{
}
uint8_t ClsRelayOnOff::getPin() { return m_RelayPin; }
void ClsRelayOnOff::setup(uint8_t relayId, uint8_t relayPin, String relayName, eOnOff_OPENCLOSE openClose)
{
    m_RelayId = relayId;
    m_RelayPin = relayPin;
    m_RelayName = relayName;
    m_openClose = openClose;

    pinMode(relayPin, OUTPUT);
    digitalWrite(m_RelayPin, m_openClose);
}
// TODO
void ClsRelayOnOff::loop() {}
void ClsRelayOnOff::setOpen() { digitalWrite(m_RelayPin, eOnOff_OPENCLOSE_OPEN); }
void ClsRelayOnOff::setClose() { digitalWrite(m_RelayPin, eOnOff_OPENCLOSE_CLOSE); }
String ClsRelayOnOff::getJson()
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
    result + "]}";

    return result;
}

uint8_t ClsRelayOnOff::getIsOpen()
{
    if (digitalRead(m_RelayPin == RELAY_OPEN))
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