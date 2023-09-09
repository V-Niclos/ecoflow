#ifndef CLSCAUDAL_H
#define CLSCAUDAL_H
#include <Arduino.h>
#include "ArduinoJson.h"
class ClsCaudal
{
private:
StaticJsonDocument<512> m_JsonDoc;
    String m_fileName = "caudal.jsn";
    uint8_t m_YearActual = 0;
    uint8_t m_MonthActual = 0;
    uint32_t m_StdYear[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t m_StdMonthsLitres[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t m_CaudalLast = 0;
    uint8_t m_previouDay = 0;
    void fileSave();
    void fileRead();

public:
    ClsCaudal(/* args */);
    ~ClsCaudal();
    void addCaudal(uint32_t year, uint32_t month, uint32_t day, uint32_t litres);
    String getStdHtml();
    void setup();
    void Loop();
};
#endif
