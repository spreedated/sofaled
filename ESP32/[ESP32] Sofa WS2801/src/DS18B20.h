#ifndef _DS18B20_H
#define _DS18B20_H
	#if defined (ENABLE_DS18B20)
		#include <DallasTemperature.h>
		#include <OneWire.h> 

		OneWire oneWire(ONE_WIRE_BUS);
		DallasTemperature sensors(&oneWire);

		void SetUp_DS18B20()
		{
			sensors.begin();

			Serial.println("| [DS18B20][SetUp] Ready");
		}

		void Loop_DS18B20()
		{
			sensors.requestTemperatures();
			float t = sensors.getTempCByIndex(0); //Use first in line of bus

			if (t <= -40.0f)
			{
				return;
			}

			Serial.println("| [DS18B20][Loop] Temp reading: \"" + String(t) + "\337C\"");

			if (t >= SHUTDOWN_TEMP_C)
			{
				colorAll(0);

				Serial.println("| [DS18B20][TEMP TOO HIGH] TEMP TOO HIGH!!!");

				MQTT_Publish("{\"homecode\":\"10011\", \"socket\":\"01000\", \"state\":0}", "/neXn/433/nxn-nodeMCU-107/switch");
			}
		}
	#endif
#endif // !DS18B20