#ifndef MAINRESETPRESSED_H
#define MAINRESETPRESSED_H
#include <Arduino.h>
#include "mainDefines.h"
#include <RemoteDebug.h>
/// @brief update g_IsReset value
/// if is button is low  during the interval assigned to variable g_intervalPushReset, defined in mainDefines.h
void isResetPressed()
{
    g_IsReset = false;
    // debugI("isResetPressed() start - g_IsReset %d", int(g_IsReset));

    bool readedResetButton = digitalRead(g_pinReset);
    if (readedResetButton == HIGH)
    {
        return;
    }
    unsigned long intervalLOW = millis();

    while (readedResetButton == LOW)
    {
        intervalLOW = millis();
        readedResetButton = digitalRead(g_pinReset);
    }
    if (intervalLOW < g_intervalPushReset)
    {
        g_IsReset = false;
    }
    else
    {
        g_IsReset = true;
       
    }
}
#endif