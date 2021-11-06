#include "neXnEEPROM.h"

neXnEEPROM::neXnEEPROM()
{

}

neXnEEPROM::~neXnEEPROM()
{

}

void neXnEEPROM::Begin()
{
	EEPROM.begin(EEPROM_SIZE);
	Serial.println("| [EEPROM][SetUp] Ready, allocated size \"" + String(EEPROM_SIZE) + "\"");
}

uint32_t neXnEEPROM::EEPROMRead()
{
    byte r;
    byte g;
    byte b;

    r = EEPROM.read(5);
    g = EEPROM.read(6);
    b = EEPROM.read(7);

    Serial.println("| [EEPROM][Read] R: \"" + String(r) + "\" G: \"" + String(g) + "\" B: \"" + String(b) + "\"");

    return ThreeByteToDec(r, g, b);
}

void neXnEEPROM::EEPROMWrite(byte r, byte g, byte b)
{
    EEPROM.write(5, r);
    EEPROM.write(6, g);
    EEPROM.write(7, b);

    Serial.println("| [EEPROM][Write] R: \"" + String(r) + "\" G: \"" + String(g) + "\" B: \"" + String(b) + "\"");

    EEPROM.commit();
}

uint32_t neXnEEPROM::ThreeByteToDec(byte r, byte g, byte b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}