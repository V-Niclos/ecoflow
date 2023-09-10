#include "ClsFileSpiffs.h"
ClsFileSpiffs::ClsFileSpiffs(/* args */)
{
    fncSpiffsInit();
}

ClsFileSpiffs::~ClsFileSpiffs()
{
}
String ClsFileSpiffs::fileReadWithDefault(String path, String defaultContent)
{
    if (fileExist(path))
    {
        fileWrite(path, defaultContent);
    }
    return fileRead(path);
}
String ClsFileSpiffs::fileRead(String path)
{
    // Serial.println("--------------------------------READ file: start " + path);
    String result;
    if (!fncSpiffsInit())
    {
        return ("oops cant init SSPIFF  " + path);
    }

    if (!fileExist(path))
    {
        // Serial.println("ERROR  not exist  file " + path);
    }

    File file = SPIFFS.open(path);
    if (!file || file.isDirectory())
    {
        // Serial.println("- failed to open file for reading");
        return String();
    }

    while (file.available())
    {
        result = String(file.readStringUntil('\n'));

        break;
    }
    file.flush();
    file.close();
    // Serial.println("READED=" + result);

    // Serial.println("--------------------------------READ file: END " + path);

    return result;
}
bool ClsFileSpiffs::fileWrite(String path, String content)
{
     Serial.println("--------------------------------write file: start " + path);
     Serial.println("Save in"+path+" content= " + content);
    bool bResult = true;
    if (!fncSpiffsInit())
    {
        return false;
    }
    if (fileExist(path))
    {
        fileDelete(path);
    }

    File file = SPIFFS.open(path, FILE_WRITE);
    if (!file)
    {
         Serial.println("- failed to open file for writing");
        return false;
    }
    if (file.print(content))
    {
         Serial.println("ok writed");
    }
    else
    {
        // // Serial.println("- frite failed");
    }
    file.flush();
    file.close();
    // Serial.print("--------------------------------write file: end ");
    return bResult;
}
bool ClsFileSpiffs::fileExist(String path)
{
    if (!fncSpiffsInit())
    {
        return false;
    }

    bool bResult = true;
    if (SPIFFS.exists(path))
    {
        // Serial.println(path + "file exist");
    }
    else
    {
        // Serial.println(path + "file not exist");
        bResult = false;
    }
    return bResult;
}
bool ClsFileSpiffs::fileDelete(String path)
{
    bool bResult = true;
    if (fileExist(path))
    {

        bResult = SPIFFS.remove(path);
    }
    return bResult;
}

 bool ClsFileSpiffs::fncSpiffsInit()
{
    if (!SPIFFS.begin(true))
    {
        // Serial.println("An error has occurred while mounting SPIFFS");
        return false;
    }
    // Serial.println("SPIFFS mounted successfully");
    return true;
}

void ClsFileSpiffs::fileListSerial()
{

    if (!SPIFFS.begin(true))
    {
        return;
    }
    if (!SPIFFS.begin(true))
        return;
    File root = SPIFFS.open("/");

    File file = root.openNextFile();

    while (file)
    {

        // Serial.print("FILE: ");
        // Serial.println(file.name());

        file = root.openNextFile();
    }
}

 double ClsFileSpiffs::fncFileReadValueDoubleDefault(String path, double defaultValue)
{
    if (!fileExist(path))
    {
        char cDouble[14];
        dtostrf(defaultValue, 12, 7, cDouble);
        Serial.println("fncFileReadValueDoubleDefault not exist" +path);
        Serial.print(cDouble);
        fileWrite(path, String(cDouble));
    }
    return fncFileReadValueDouble(path);
}
double ClsFileSpiffs::fncFileReadValueDouble(String path)
{
     Serial.println("=================== fncFileReadValueDouble ======================");
     Serial.printf("\n\rReading file: %s value: ", path);
    double dFileContent = 0;
    String sFileContent = "";
    char *tok;
    File file = SPIFFS.open(path);
    if (!file || file.isDirectory())
    {
        // Serial.println("- failed to open file for reading");
        return 0;
    }

    while (file.available())
    {
        sFileContent = String(file.readStringUntil('\n'));

        break;
       
        // Serial.print(sFileContent);
        // Serial.print(" tranformado ");
        // Serial.println(dFileContent, 9);

        // Serial.println("=================== fncFileReadValueDouble END======================");
       
    }
    Serial.println(sFileContent);
     dFileContent = strtod(sFileContent.c_str(), &tok);
     return dFileContent;
}