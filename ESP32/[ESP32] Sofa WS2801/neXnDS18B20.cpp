#include "neXnDS18B20.h"

neXnDS18B20::neXnDS18B20(int oneWireBusPin)
{
	oneWire = OneWire(oneWireBusPin);
	sensors = DallasTemperature(&oneWire);
}

neXnDS18B20::~neXnDS18B20()
{

}

void neXnDS18B20::Begin()
{
	sensors.begin();
	Serial.println("| [DS18B20][Begin] Ready");
}

int neXnDS18B20::Handle(int busId)
{
	sensors.requestTemperatures();
	return sensors.getTempCByIndex(busId);
}

bool neXnDS18B20::IsAvailable(int busId)
{
	sensors.requestTemperatures();
	float t = sensors.getTempCByIndex(busId);

	if (t <= -120.0f)
	{
		return false;
	}
	return true;
}