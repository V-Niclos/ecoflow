#ifndef CLSRELAYONOFF
#define CLSRELAYONOFF
#include <Arduino.h>
#define RELAY_OPEN 0
#define RELAY_CLOSE 1
class ClsRelayOnOff
{
  public:
    ClsRelayOnOff(/* args */);
    ~ClsRelayOnOff();
     enum eOnOff_OPENCLOSE {    eOnOff_OPENCLOSE_OPEN ,eOnOff_OPENCLOSE_CLOSE };
    uint8_t getIsOpen();
    void setOpen();
    void setClose();
    void setup( uint8_t relayId,  uint8_t relayPin,   String relayName ,eOnOff_OPENCLOSE openClose);
    void loop();
   uint8_t getPin();
   String getJson();
   String getHtmlStatus();
private:
    uint8_t m_RelayId;
    uint8_t m_RelayPin;
    String m_RelayName = "";
    
   eOnOff_OPENCLOSE m_openClose=eOnOff_OPENCLOSE_CLOSE;


};
#endif
