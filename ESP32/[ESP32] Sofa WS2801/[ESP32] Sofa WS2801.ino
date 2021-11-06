//2021 (c) neXn-Systems

#include "config.h"
#include "neXnSerial.h"
#include "src/Helper.h"
#include "neXnEEPROM.h"
#include "neXnWS2801.h"
//#include "neXnMQTT.h"
#include "neXnBluetooth.h"
//#include "neXnOTA.h"
#include "neXnDS18B20.h"
#include "libs/neXn.WiFi/neXn.WiFi.h"
#include <ArduinoJson.h>

neXnSerial ser(SERIAL_BAUD);
neXnBluetooth bt(BLUETOOTH_NAME);
neXnEEPROM eep;
neXnWS2801 ws(PixelCount, dataPin, clockPin);
neXnDS18B20 tsens(ONE_WIRE_BUS);
neXnWiFi wifi;
neXnWiFiConfig wifiConfig;
//neXnMQTT mq;
//neXnOTA ota(otaPort, clientID, otaMD5Password, true);

void setup() {
    ser.Begin();
    Serial.print("Welcome to the neXn-Systems NodeMCU v");
    Serial.println(nodeVersion);
    
    eep.Begin();
    ws.Begin();
    bt.Begin();
    wifiConfig = neXnWiFiConfig(WiFi_IP, WiFi_DNSServer, WiFi_Gateway, WiFi_Gateway);
    wifi = neXnWiFi((char*)WiFi_SSID, (char*)WiFi_Password, (char*)WiFi_Hostname, wifiConfig);
    wifi.Begin();
    //mq = neXnMQTT(String(mqtt_server), String(clientID), wifi.net);
    //ota.Begin();
    tsens.Begin();
}

void loop() {
    //Bluetooth handle
    String bts = bt.Handle();
    if (bts.length() > 0)
    {
        ws.ColorAll(JSONToDec(bts));
    }
    //# ### #

    //RestartIfNecessary();
    wifi.Handle();
    //MQTT_PublishAlive();

    if (tsens.IsAvailable(0) && tsens.Handle(0) >= SHUTDOWN_TEMP_C)
    {
        ws.ColorAll(0);
        Serial.println("| [TEMP TOO HIGH] TEMP TOO HIGH!!!");
        //mq.Publish("{\"homecode\":\"10011\", \"socket\":\"01000\", \"state\":0}", "/neXn/433/nxn-nodeMCU-107/switch");
    }
    
    delay(200); //Small delay
}

uint32_t JSONToDec(String payload)
{
    DynamicJsonDocument doc(1024);

    StaticJsonDocument<64> filter;
    filter["g"] = true;
    filter["b"] = true;
    filter["r"] = true;

    deserializeJson(doc, payload, DeserializationOption::Filter(filter));

    byte r;
    byte g;
    byte b;

    r = doc["r"];
    g = doc["g"];
    b = doc["b"];

    return ws.ThreeByteToDec(r,g,b);
}