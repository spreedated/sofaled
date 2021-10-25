#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

    #if defined (ENABLE_BLUETOOTH)
        #include <BTScan.h>
        #include <BTAdvertisedDevice.h>
        #include <BTAddress.h>
        #include <BluetoothSerial.h>

        #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
        #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
        #endif

        BluetoothSerial SerialBT;

        void SetUp_Bluetooth()
        {
	        SerialBT.begin(BLUETOOTH_NAME);

            Serial.println("| [Bluetooth][SetUp] Ready");
        }

        void Loop_Bluetooth()
        {
            if (SerialBT.available())
            {
                String pp = SerialBT.readString();
                Serial.println(" | [Bluetooth] Received: \"" + pp + "\"");

                MQTT_CommandColor(pp);
            }
        }
    #endif

#endif // !BLUETOOTH