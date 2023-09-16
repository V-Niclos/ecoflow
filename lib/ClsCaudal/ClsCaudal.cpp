#include <ClsCaudal.h>
#include "ClsFileSpiffs.h"
ClsCaudal::ClsCaudal(/* args */) {}
ClsCaudal::~ClsCaudal() {}

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
void ClsCaudal::setupsetup(uint8_t id, uint8_t pin, String Name, uint8_t stddCurrrentYear, uint8_t stdCurrentMonth)
{

    m_id = id;
    m_pin = pin;
    m_name = Name;
    m_stdCurrentYear = stddCurrrentYear;
    m_CurrentMonth = stdCurrentMonth;
}

void ClsCaudal::fileSave((uint8_t stdCurrentYear, uint8_t stdCurrentMonth)
{
    String fileNameYear = m_stdFileNamePrefix + String(m_id) + String(stdCurrentYear);
    String fileNameMonth = m_file = fileNameYear String(stdCurrentMonth);

    //{"year": "2000",	"1": "1","2": "12", "3": "133",... "12":"213"}
    String sJsonYear = "{\"year\":\"+ (stdCurrentYear)+"\"";
    for (uint8_t i = 0; i < 12, i++)
    {
        sJsonYear +=", \"+String(i)+"\":\""  String(stdfile_MonthsOfYear_Save[i]) + "\"");
    }
    sJsJsonYearson += "}";
    ClsFileSpiffs::fileWrite(fileNameYear, sJsonYear);
    // {"year": "2000", "month";"12",	"1": "1","2": "12", "3": "133",... "31":"13"}
    String sJsonMonth = "{\"year\":\"+ (stdCurrentYear)+"\", \"month\":\"" + String(stdCurrentMonth) + "\"";
    for (uint8_t i = 0; i < 31, i++)
    {
        sJsonMonth +=", \"+String(i)+"\":\""  String(m_StdLitresDayByMonthh[i]) + "\"");
    }
    sJsonMonth += "}";
    ClsFileSpiffs::fileWrite(fileNameYear, sJsonMonth);)
    // save std of month by day
    //{"year": "2000",	"1": "1","2": "12", "3": "133",... "12":"213"}


}

void ClsCaudal::fileRead(uint8_t stdCurrentYear, uint8_t stdCurrentMonth)
{
    String fileNameYear = m_stdFileNamePrefix + String(m_id) + String(stdCurrentYear);
    String fileNameMonth = m_file = fileNameYear String(stdCurrentMonth);
    // if not exist file then values to 0
    if (!ClsFileSpiffs::fileExist(fileNameYear))
    {
        m_StdLitresMonthByYear = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    if (!ClsFileSpiffs::fileExist(fileNameMonth))
    {
        m_StdLitresDayByMonthh[31] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        String sJsonYear = ClsFileSpiffs::fileRead(fileNameYear);
        DeserializationError error = deserializeJson(m_JsonDoc, sJsonYear);
        if (error)
        {
            debugE("deserializeJson() failed: %s", error.c_str());
            return;
        }
        for (int i = 0; i < 12; i++)
        {
            m_StdLitresMonthByYear[i] = m_JsonDoc[i].as<int>();
        }
    }