//2021 (c) neXn-Systems

#include "config.h"
#include "src/Serial.h"
#include "src/Helper.h"
#include "src/EEPROM.h"
#include "src/WS2801.h"
#include "src/WiFi.h"
#include "src/MQTT.h"
#include "src/Bluetooth.h"
#include "src/OTA.h"
#include "src/DS18B20.h"

void setup() {
    SetUp_Serial();
    SetUp_WS2801();
    SetUp_EEPROM();
    SetUp_Bluetooth();
    SetUp_WiFi();
    SetUp_MQTT();
    //SetUp_OTA();
    SetUp_DS18B20();
}

void loop() {
    Loop_Bluetooth();
    RestartIfNecessary();
    //ArduinoOTA.handle();
    Loop_MQTT();
    Loop_WiFi();
    MQTT_PublishAlive();
    Loop_WS2801();
    Loop_DS18B20();

    delay(5); //Small delay
}