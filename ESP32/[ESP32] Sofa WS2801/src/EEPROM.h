#ifndef _EEPROM_H
#define _EEPROM_H

#include <EEPROM.h>

constexpr auto EEPROM_SIZE = 3;

//bool EEPROMReadPulse()
//{
//    bool acc = EEPROM.readByte(3);
//    Serial.println("| [EEPROM][ReadPulse] Pulse: \"" + String(acc));
//
//    return acc;
//}

uint32_t EEPROMRead()
{
    byte r;
    byte g;
    byte b;

    r = EEPROM.readByte(0);
    g = EEPROM.readByte(1);
    b = EEPROM.readByte(2);

    Serial.println("| [EEPROM][Read] R: \"" + String(r) + "\" G: \"" + String(g) + "\" B: \"" + String(b) + "\"");

    return ThreeByteToDec(r, g, b);
}
void EEPROMWrite(byte r, byte g, byte b)
{
    EEPROM.writeByte(0, r);
    EEPROM.writeByte(1, g);
    EEPROM.writeByte(2, b);

    Serial.println("| [EEPROM][Write] R: \"" + String(r) + "\" G: \"" + String(g) + "\" B: \"" + String(b) + "\"");

    EEPROM.commit();
}

void SetUp_EEPROM()
{
    EEPROM.begin(EEPROM_SIZE);
    
    Serial.println("| [EEPROM][SetUp] Ready, allocated size \"" + String(EEPROM_SIZE) + "\"");
}

#endif // !EEPROM