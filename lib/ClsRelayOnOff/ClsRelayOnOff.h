#ifndef CLSRELAYONOFF
#define CLSRELAYONOFF
#include <Arduino.h>
#include "RemoteDebug.h"
extern RemoteDebug Debug;
class ClsRelayOnOff
{
  public:
    ClsRelayOnOff(/* args */);
    ~ClsRelayOnOff();
        enum eOPENCLOSE {    eOPENCLOSE_OPEN ,eOPENCLOSE_CLOSE };
     
    uint8_t getIsOpen();
    void setOpen();
    void setClose();
    void setup( uint8_t relayId,  uint8_t relayPin,   String relayName ,eOPENCLOSE eOpenClose);
    void loop(bool isReset);
   uint8_t getPin();
   String getJsonFromValues();
   String getHtmlStatus();
private:
    uint8_t m_RelayId;
    uint8_t m_RelayPin;
    String m_RelayName = "";
    
   eOPENCLOSE m_openClose=eOPENCLOSE_CLOSE;
void fncResetFactory();

};
#endif
