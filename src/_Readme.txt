---------------------------------------------------------------------------------
Gazapo web socket  para solucionar sha.h no encontrado
cambiar en `
C:\Users\vteni\OneDrive\Documentos\PlatformIO\Projects\riego_24_0508\.pio\libdeps\firebeetle32\RemoteDebug\src\utility\websockets.cpp
el parrafo para que utilice sha.h correspondiente

#ifdef ESP8266
#include <Hash.h>
#elif defined(ESP32)
//#include <hwcrypto/sha.h>
  #if ESP_IDF_VERSION_MAJOR >= 4
    #if ( ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(1, 0, 6) )
      #include "sha/sha_parallel_engine.h"
    #else
      #include <esp32/sha.h>
    #endif  
  #else
    #include <hwcrypto/sha.h>
  #endif
#else

extern "C" {
#include "libsha1/libsha1.h"
}

#endif
---------------------------------------------------------------------------------

datetime manipulation
DateTime stopTime = rtc.now();
DateTime StopTimePlusTwoHoursAndThirtyMinutes = stopTime + TimeSpan(0, 2, 30, 0);
https://adafruit.github.io/RTClib/html/class_date_time.html