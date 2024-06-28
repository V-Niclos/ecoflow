#ifndef MAINFLOWSENSOR_H
#define MAINFLOWSENSOR_H
#include <arduino.h>
#include <FlowSensor.h>
#include "mainDefines.h"
//------------------------
// Sensor Type
// YFS201;
// YFB1;
// OF10ZAT;
// OF10ZZT;
// OF05ZAT;
// OF05ZZT;
#define flowSensorType YFB1
#define FLOW_SENSOR_TYPE YFB1
#define MCU_ESP32_ESP8266								  // ESP286
FlowSensor g_flow_sensor(FLOW_SENSOR_TYPE, g_pinSensor2); // 33
unsigned long g_flow_interval_previous = 0;				  // Same FLOW_SENSOR_TYPE as millis()
unsigned long g_flow_interval_Switch = 10000;			  // read values
void IRAM_ATTR fnc_flow_count()
{
	g_flow_sensor.count();
}
void fncFlow_Setup()
{
	g_flow_sensor.begin(fnc_flow_count);
}
String fncFlow_TextValues()
{
	String szResult = "Now Flow rate\t L/minute= ";
	szResult.concat(String(g_flow_sensor.getFlowRate_m()));
	szResult.concat("\t Volume= ");
	szResult.concat(String(g_flow_sensor.getVolume()));
	return szResult;
}
void fncFlow_ShowValues()
{
	g_flow_sensor.read();
	Serial.print("Now Flow rate\t L/minute= ");
	Serial.print(g_flow_sensor.getFlowRate_m());
	Serial.print("\t Volume= ");
	Serial.println(g_flow_sensor.getVolume());
	g_flow_interval_previous = millis();
}
void fncFlow_Loop()
{
	if (millis() - g_flow_interval_previous <g_flow_interval_Switch)
	{
	return;
		
	}

	bool bSetData = false;
	uint32_t litres_1 = 0;
	uint32_t litresMinute_1 = 0;
	uint32_t litres_2 = 0;
	uint32_t litresMinute_2 = 0;

	g_flow_sensor.read();
	if (g_Relays.m_RelaysIrrigationPrg[0].getRelayIsOpen())
	{
		litres_1 = (int32_t)g_flow_sensor.getVolume();
		litresMinute_1 =(int32_t)g_flow_sensor.getFlowRate_m();
		bSetData = true;
	}
	if (g_Relays.m_RelaysIrrigationPrg[1].getRelayIsOpen())
	{
		litres_2 = (int32_t)g_flow_sensor.getVolume();
		litresMinute_2 =(int32_t)g_flow_sensor.getFlowRate_m();
		bSetData = true;
	}
	if(bSetData)
	{
		g_ThingSpeak.setData(g_TimeRtcNtp.nowDateTime_lastRead(),litres_1,litres_2,litresMinute_1 ,litresMinute_2);
			g_ThingSpeak.loop();

	}
}

#endif