/*
GPIO  DEVICE     FUNCTION
12    RELAY 1    IRRIGATION
04    RELAY 2    IRRIGATION
27    RELAY 3    
26    RELAY 4
25    RELAY 5
00    BUTTON     FLASH
17    BUTTON     REBOOT 
32    FLOW 1     CAUDALIMETER
33    FLOW 2     CAUDALIMETER
34    LED 1
35    LED 2
02    LED         BLUE INTERNAL(TRANSMISION)
01    TXD         
03    RXD
21    SDA         I2C RTC
22    SLC         I2C RTC
37    SPI_MOSI    
32    SPI_MISO
30    SPI_SCK

*/
#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "ClsRelays.h"
#include "ClsRelayIrrigationPrg.h"
#include "ClsTimeRtcNtp.h"
#include "ClsNetworkConfig.h"
#include "ClsSunSetRise.h"
#define SERIAL_BAUDRATE 115200
StaticJsonDocument<2088> g_docJsonRelays;
ClsTimeRtcNtp g_TimeRtcNtp;
ClsSunSetRise g_SunSetRise;
ClsNetworkConfig g_NetworkConfig;
//------ RELAYS
uint32_t g_RelayDelayLoop = 1;
const uint g_RelaysCount = 5;


ClsRelays g_Relays;
//------ HADWARE PINS USED
const int8_t g_pinReset = 17;
const uint8_t g_pinIntLedBlue = 13;
const uint8_t g_pinIntLedRed = 14;

const uint8_t g_pingSensorLed = 23;

//const uint8_t g_pinRelays[g_RelaysCount] = {23, 19, 4, 13, 13}; //  for testing with testing board with only four relays
const uint8_t g_pinRelays[g_RelaysCount] = {12, 04, 27, 26, 25}; // for use with explotation board


const uint8_t g_pinI2C_SDA = 21;
const uint8_t g_pinI2C_SCL = 22;

const uint8_t g_pinSPI_CS   = 5;
const uint8_t g_pinSPI_MOSI = 23;
const uint8_t g_pinSPI_MISO = 19;
const uint8_t g_pinSPI_SCK  = 18;

const uint8_t g_pinSensor1 = 32;
const uint8_t g_pinSensor2 = 33;

const uint8_t g_pinVinSensor = 36;

// const uint g_pinRelays[g_RelaysCount] = {26, 25, 33, 32};
// int g_pinRelays[8] = {23, 21, 19, 4, 25, 16, 13, 26};
// int g_pinRelays[g_RelaysCount] =   {23, 21, 19, 4, 25, 16, 13, 26};
//-------------- NET SERVICES

AsyncWebServer g_NetWebServer(80);



#endif