
#ifndef ClsFileSpiffS_H
#define ClsFileSpiffS_H

#include "SPIFFS.h"
#include "Arduino.h"
#include "RemoteDebug.h"
extern RemoteDebug Debug;
class ClsFileSpiffs
{
private:
public:
    ClsFileSpiffs(/* args */);
    ~ClsFileSpiffs();
    static bool begin();
    static String fileReadWithDefault(String path, String defaultContent);
    static String fileRead(String path);
    static bool fileWrite(String path, String content);
    static bool fileExist(String path);
    static bool fileDelete(String path);
    static void fileListSerial();
    static double fncFileReadValueDouble(String path);
    static double fncFileReadValueDoubleDefault(String path, double defaultValue);
};
#endif
