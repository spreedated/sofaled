#include "neXnWS2801.h"

neXnWS2801::neXnWS2801(uint16_t pixelCount, uint8_t dataPin, uint8_t clockPin)
{
	neXnWS2801::pixelCount = pixelCount;
	neXnWS2801::dataPin = dataPin;
	neXnWS2801::clockPin = clockPin;
	
	strip = Adafruit_WS2801(pixelCount, dataPin, clockPin);
}

neXnWS2801::~neXnWS2801()
{
	strip.~Adafruit_WS2801();
}

void neXnWS2801::Begin()
{
	strip.begin();
	strip.show(); // Turn OFF all pixels ASAP

	Serial.println("| [WS2810][SetUp] Ready");
}

void neXnWS2801::ColorAll(uint32_t c)
{
	for (int i = strip.numPixels(); i > -1; i--)
	{
		strip.setPixelColor(i, c);
	}
	strip.show();

	Serial.println("| [WS2801][ColorAll] Set all pixels to \"" + String(c) + "\"");
}

// fill the dots one after the other with said color
// good for testing purposes
void neXnWS2801::ColorWipe(uint32_t c, uint8_t wait)
{
	for (int i = strip.numPixels(); i > -1; i--)
	{
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
	}
}
//Theatre-style crawling lights with rainbow effect
void neXnWS2801::TheaterChaseRainbow(uint8_t wait)
{
	for (int j = 0; j < 255; j++) {     // cycle all 256 colors in the wheel
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, ThreeByteToDec(j, j, j));    //turn every third pixel on
			}
			strip.show();

			delay(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
		Serial.println(j);
	}
}

uint32_t neXnWS2801::ThreeByteToDec(byte r, byte g, byte b)
{
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;
	c |= b;
	return c;
}

byte* neXnWS2801::DecToThreeByte(uint32_t dec)
{
	byte* c;
	c[0] = dec >> 16;
	c[1] = (dec / 256) & 255;
	c[2] = dec & 255;

	return c;
}