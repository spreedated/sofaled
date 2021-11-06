#ifndef _NEXNEEPROM_H
#define _NEXNEEPROM_H

#include <EEPROM.h>

#define EEPROM_SIZE 8

class neXnEEPROM
{
public:
	neXnEEPROM();
	~neXnEEPROM();
	void Begin();
	uint32_t EEPROMRead();
	void EEPROMWrite(byte r, byte g, byte b);
private:
	uint32_t ThreeByteToDec(byte r, byte g, byte b);
};

#endif // !_NEXNEEPROM_H
