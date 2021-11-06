#include "neXnSerial.h"

neXnSerial::neXnSerial(unsigned long baudrate)
{
    neXnSerial::serialBaud = baudrate;
}

neXnSerial::~neXnSerial()
{

}

void neXnSerial::Begin()
{
    Serial.begin(serialBaud);
    while (!Serial) {
        ; // wait for serial port to connect.
    }
}
