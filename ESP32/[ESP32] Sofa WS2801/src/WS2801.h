#ifndef _WS2801_H
#define _WS2801_H
	#if defined (ENABLE_WS2801)
		#include <SPI.h>
		#include <Adafruit_WS2801.h>

		Adafruit_WS2801 strip = Adafruit_WS2801(PixelCount, dataPin, clockPin);
		bool doPulse;

		void colorAll(uint32_t c)
		{
			for (int i = strip.numPixels(); i > -1; i--)
			{
				strip.setPixelColor(i, c);
			}
			strip.show();
		}

		// fill the dots one after the other with said color
		// good for testing purposes
		void colorWipe(uint32_t c, uint8_t wait)
		{
			for (int i = strip.numPixels(); i > -1; i--)
			{
				strip.setPixelColor(i, c);
				strip.show();
				delay(wait);
			}
		}
		//Theatre-style crawling lights with rainbow effect
		void theaterChaseRainbow(uint8_t wait)
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

		byte pulseR;
		byte pulseG;
		byte pulseB;
		bool stepUp;
		int pWait = 100;
		void colorPulse()
		{
			if (pulseR <= 0 || pulseB <= 0 || pulseG <= 0)
			{
				stepUp = true;
			}
			if (pulseR >= 255 || pulseB >= 255 || pulseG >= 255)
			{
				stepUp = false;
			}
			if (!stepUp)
			{
				pulseR--;
				pulseG--;
				pulseB--;
			}
			else
			{
				pulseR++;
				pulseG++;
				pulseB++;
			}

			for (int i = strip.numPixels(); i > -1; i--)
			{
				colorAll(ThreeByteToDec(pulseR, pulseG, pulseB));
			}

			if (pWait > 0)
			{
				delay(pWait);
			}
		}

		void SetUp_WS2801()
		{
			strip.begin();
			strip.show(); // Turn OFF all pixels ASAP

			colorAll(EEPROMRead());

			Serial.println("| [WS2810][SetUp] Ready");
		}

		void Loop_WS2801()
		{
			//if ((millis() / 1000) >= 60)
			//{
			//	colorAll(EEPROMRead());
			//}
			if (doPulse)
			{
				colorPulse();
				Serial.println("RGB: " + String(pulseR) + "," + String(pulseG) + "," + String(pulseB));
			}
		}
	#endif
#endif // !WS2801