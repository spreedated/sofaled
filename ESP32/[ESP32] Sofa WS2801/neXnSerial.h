#ifndef _NEXNSERIAL_H
#define _NEXNSERIAL_H

#include <Arduino.h>

class neXnSerial
{
public:
	neXnSerial(unsigned long baudrate);
	~neXnSerial();
	void Begin();
private:
	unsigned long serialBaud;
};
	 
#endif // !_NEXNSERIAL_H