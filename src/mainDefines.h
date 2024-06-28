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
13    LED 1
14    LED 2
02    LED         BLUE INTERNAL(TRANSMISION)
01    TXD
03    RXD
21    SDA         I2C RTC //https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/
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
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include <FlowSensor.h>
#include "ClsRelays.h"
#include "ClsRelayIrrigationPrg.h"
#include "ClsTimeRtcNtp.h"
#include "ClsNetworkConfig.h"
#include "ClsThingSpeak.h"

// #include "ClsSunset.h"
#if ESP_IDF_VERSION_MAJOR >= 4
#if (ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(1, 0, 6))
#include "sha/sha_parallel_engine.h"
#else
#include <esp32/sha.h>
#endif
#else
#include <hwcrypto/sha.h>
#endif
// #include <esp32/sha.h>
#include <DNSServer.h>
#include "ESPmDNS.h"

// #include "RemoteDebug.h"
#define SERIAL_BAUDRATE 115200
#define HIGH_INT_LED 0
#define LOW_INT_LED 1

#include "RemoteDebug.h"
//------ HADWARE PINS USED
//------------------
const int8_t g_pinReset = 17;
const uint8_t g_pinLedFlash = 13;
const uint8_t g_pinIntLedRed = 14;
//------ RELAYS
uint32_t g_RelayDelayLoop = 1;
const uint g_RelaysCount = 5;
// const uint8_t g_pinRelays[g_RelaysCount] = {23, 19, 4, 13, 13}; //  for testing with testing board with only four relays
const uint8_t g_pinRelays[g_RelaysCount] = {12, 4, 27, 26, 25}; // for use with explotation board

const uint8_t g_pinI2C_SDA = 21;
const uint8_t g_pinI2C_SCL = 22;

const uint8_t g_pinSPI_CS = 5;
const uint8_t g_pinSPI_MOSI = 23;
const uint8_t g_pinSPI_MISO = 19;
const uint8_t g_pinSPI_SCK = 18;

const uint8_t g_pinSensor1 = 32;
const uint8_t g_pinSensor2 = 33;

const uint8_t g_pinVinSensor = 36;

//-----------------------------------------------------------------------------

const bool g_bResetFactoryRelays=false;
const bool g_bResetFactoryNetwork=false;

RemoteDebug Debug;
// StaticJsonDocument<2088> g_docJsonRelays;
JsonDocument g_docJsonRelays;
ClsTimeRtcNtp g_TimeRtcNtp;
// ClsSunset g_SunSetRise;
ClsNetworkConfig g_NetworkConfig;
ClsThingSpeak g_ThingSpeak;

bool g_IsReset = false;
bool g_IsRtcConfigChanged = false;
const uint32_t g_intervalPushReset = 10000;

ClsRelays g_Relays;
unsigned long ota_progress_millis = 0;
AsyncWebServer g_NetWebServer(80);
//---------------------

#endif