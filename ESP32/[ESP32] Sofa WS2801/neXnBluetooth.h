#ifndef _NEXNBLUETOOTH_H
#define _NEXNBLUETOOTH_H

#include <BTScan.h>
#include <BTAdvertisedDevice.h>
#include <BTAddress.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

class neXnBluetooth
{
public:
	neXnBluetooth(String bluetoothName);
	~neXnBluetooth();
	void Begin();
	String Handle();
private:
	BluetoothSerial SerialBT;
	String bluetoothName;
};

#endif // !_NEXNBLUETOOTH_H