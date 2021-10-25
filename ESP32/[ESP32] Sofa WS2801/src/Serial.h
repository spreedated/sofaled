#ifndef _SERIAL_H
#define _SERIAL_H

    #if defined (ENABLE_SERIAL)
        void SetUp_Serial()
        {
            Serial.begin(SERIAL_BAUD);
            while (!Serial) {
                ; // wait for serial port to connect.
            }
        }
    #endif

#endif // !SERIAL