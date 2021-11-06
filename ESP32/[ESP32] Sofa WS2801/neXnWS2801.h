#ifndef _NEXNWS2801_H
#define _NEXNWS2801_H

#include <SPI.h>
#include <Adafruit_WS2801.h>

class neXnWS2801
{
public:
	neXnWS2801(uint16_t pixelCount, uint8_t dataPin, uint8_t clockPin);
	~neXnWS2801();
	void Begin();
	void ColorAll(uint32_t c);
	void ColorWipe(uint32_t c, uint8_t wait);
	void TheaterChaseRainbow(uint8_t wait);
	static uint32_t ThreeByteToDec(byte r, byte g, byte b);
	static byte* DecToThreeByte(uint32_t dec);
private:
	Adafruit_WS2801 strip;
	uint16_t pixelCount;
	uint8_t dataPin;
	uint8_t clockPin;
};

#endif // !_NEXNWS2801_H