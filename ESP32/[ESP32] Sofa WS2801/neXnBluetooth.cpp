#include "neXnBluetooth.h"

neXnBluetooth::neXnBluetooth(String bluetoothName)
{
	neXnBluetooth::bluetoothName = bluetoothName;
}

neXnBluetooth::~neXnBluetooth()
{
    SerialBT.~BluetoothSerial();
}

void neXnBluetooth::Begin()
{
	SerialBT.begin(bluetoothName);
	Serial.println("| [Bluetooth][SetUp] Ready");
}

String neXnBluetooth::Handle()
{
    if (SerialBT.available())
    {
        String pp = SerialBT.readString();
        Serial.println(" | [Bluetooth] Received: \"" + pp + "\"");

        return pp;
    }
    
    return String();
}
