#include <ClsCaudal.h>
#include "ClsFileSpiffs.h"
ClsCaudal::ClsCaudal(/* args */)
{
}

ClsCaudal::~ClsCaudal()
{
}
void ClsCaudal::fileSave()
{

    String sJson = "[";
    for (uint8_t i = 0; i < 12, i++)
    {
        if (i > 0)
        {
            sJson += ", ";
            sJson += "{\"year\":}" + (String(m_StdYear[i]) + ", \"litres\":" + String(m_StdMonthsLitres[i]) + "}");
        }
        sJson += "]";
        ClsFileSpiffs::fileWrite(m_fileName, sJson);)
    }
}
void ClsCaudal::fileRead()
{
    String sJson = ClsFileSpiffs::fileRead(m_fileName);
 DeserializationError error = deserializeJson(m_JsonDoc, sJson);
  if (error)
  {
    debugE("deserializeJson() failed: %s", error.c_str());
    return;
  }
  for (int i=0;i<12;i++)
  {
  m_StdYear[i]=m_JsonDoc[i]["year"].as<int>();
  m_StdMonthsLitres[i]=m_JsonDoc[i]["month"].as<int>();
  }
}
void ClsCaudal::addCaudal(uint32_t year, uint32_t month, uint32_t day, uint32_t litres)
{
    if (m_StdYear[month] != year)
    {
        m_StdYear[month] = year;
        m_StdMonthsLitres[month] = litres;
    }
    else
    {
        m_StdMonthsLitres[month] += litres;
    }
    if (day<> m_previouDay)
    {
        m_previouDay = day;
        fileSave()
    }
}

void ClsCaudal::setup() {}
