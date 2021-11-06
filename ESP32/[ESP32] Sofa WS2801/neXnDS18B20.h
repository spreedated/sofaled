#ifndef _NEXNDS18B20_H
#define _NEXNDS18B20_H

#include <DallasTemperature.h>
#include <OneWire.h> 

class neXnDS18B20
{
public:
	neXnDS18B20(int oneWireBusPin);
	~neXnDS18B20();
	void Begin();
	int Handle(int busId);
	bool IsAvailable(int busId);
private:
	OneWire oneWire;
	DallasTemperature sensors;
};

#endif // !_NEXNDS18B20_H