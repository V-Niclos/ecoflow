
#ifndef ClsFileSpiffS_H
#define ClsFileSpiffS_H
#include "SPIFFS.h"
#include "Arduino.h"

class ClsFileSpiffs
{
private:
public:
    ClsFileSpiffs(/* args */);
    ~ClsFileSpiffs();
    static bool fncSpiffsInit();
    static String fileRead(String path);
    static bool fileWrite(String path, String content);
    static bool fileExist(String path);
    static bool fileDelete(String path);
    static void fileListSerial() ;
};
#endif
