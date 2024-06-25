#ifndef MAINSETUPRELAYS_H
#define MAINSETUPRELAYS_H
#include "mainDefines.h"
#include "ClsRelayIrrigationPrg.h"

void fncMainSetupRelays(bool bResetFactoryRelays)
{

    g_Relays.setup(g_pinRelays[0], g_pinRelays[1], g_pinRelays[2], g_pinRelays[3], g_pinRelays[4], bResetFactoryRelays);
  
}
#endif