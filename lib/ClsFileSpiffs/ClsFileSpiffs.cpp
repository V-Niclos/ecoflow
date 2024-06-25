#include    "ClsFileSpiffs.h"
ClsFileSpiffs::ClsFileSpiffs(/* args */)
{
}

ClsFileSpiffs::~ClsFileSpiffs()
{
}

bool ClsFileSpiffs::begin()
{
    if (!SPIFFS.begin(true))
    {
        //debugE("error initializing SPIFFS");
        return false;
    }

    return true;
}

String ClsFileSpiffs::fileReadWithDefault(String path, String defaultContent)
{
    String result = "";
    if (!fileExist(path))
    {

        fileWrite(path, defaultContent);
    }
    result = fileRead(path);
    //debugI("OK file : %s readed, value=%s ", path.c_str(), result.c_str());
    return result;
}
String ClsFileSpiffs::fileRead(String path)
{
    String result;

    if (!fileExist(path))
    {
        //debugI("ERROR file does not exist: %s", path.c_str());
        return String();
    }

    File file = SPIFFS.open(path);
    if (!file || file.isDirectory())
    {
        debugE("FILE READ FAILED to open file for reading: %s", path.c_str());
        return String();
    }

    while (file.available())
    {
        result = String(file.readStringUntil('\n'));

        break;
    }
   debugI("FILE READ OK file : %s readed, \n value=%s ", path.c_str(), result.c_str());
    file.flush();
    file.close();
    return result;
}
bool ClsFileSpiffs::fileWrite(String path, String content)
{
    //debugI("Save in %s content= %s", path.c_str(), content.c_str());
    bool bResult = true;

    if (fileExist(path))
    {
        fileDelete(path);
    }

    File file = SPIFFS.open(path, FILE_WRITE);
    if (!file)
    {
        debugE("failed to open file for writing %s", path.c_str());
        return false;
    }
    if (file.print(content))
    {
        debugI("Ok  file saved %s", path.c_str());
        debugI("Ok  file writed %s",content.c_str());
    }
    else
    {
        //debugE("write failed to %s", path.c_str());
    }
    file.flush();
    file.close();
    return bResult;
}
bool ClsFileSpiffs::fileExist(String path)
{
    bool bResult = SPIFFS.exists(path);
    if (!bResult)
    {
        //debugI("fileExist : %s false", path.c_str());
    }
    else
    {
       //debugI("fileExist : %s true", path.c_str());
    }
    return bResult;
}

bool ClsFileSpiffs::fileDelete(String path)
{
    bool bResult = true;
    if (fileExist(path))
    {
        //debugI("delete file: %s", path.c_str());
        bResult = SPIFFS.remove(path);
    }
    return bResult;
}

void ClsFileSpiffs::fileListSerial()
{

    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    //debugI("Listing files:");
    while (file)
    {
        file = root.openNextFile();
        //debugI(" - %s", file.name());
    }
}

double ClsFileSpiffs::fncFileReadValueDoubleDefault(String path, double defaultValue)
{
    if (!fileExist(path))
    {
        char cDouble[14];
        dtostrf(defaultValue, 12, 7, cDouble);
        //debugW("fncFileReadValueDoubleDefault not exist %s, writing default %lf", path.c_str(), cDouble);
        fileWrite(path, String(cDouble));
    }
    return fncFileReadValueDouble(path);
}
double ClsFileSpiffs::fncFileReadValueDouble(String path)
{
    double dFileContent = 0;
    String sFileContent = "";
    char *tok;
    File file = SPIFFS.open(path);
    if (!file || file.isDirectory())
    {
        return 0;
    }

    while (file.available())
    {
        sFileContent = String(file.readStringUntil('\n'));

        break;
    }
    //debugV("reading %s: %s", path.c_str(), sFileContent.c_str());
    dFileContent = strtod(sFileContent.c_str(), &tok);
    return dFileContent;
}