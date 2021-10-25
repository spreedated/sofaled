#ifndef _MQTT_H
#define _MQTT_H

#include <ArduinoJson.h>
#include <MQTTClient.h>
#include <MQTT.h>

unsigned long lastMillis = 0;
MQTTClient client;
WiFiClient net;

void MQTT_Publish(String msg, const char* topic = NULL)
{
    if (topic == NULL)
    {
        topic = (String(preifxTopic) + "response").c_str();
    }

    if (!client.publish(topic, msg, false, 0))
    {
        client.connect(clientID);
        delay(10);
        client.publish(topic, msg, false, 0);
    }
}

void MQTT_PublishAlive()
{
    if (millis() - lastMillis > 10000) {
        if (!client.connected()) {
            Serial.print("| [MQTT] LastError: ");
            Serial.println(client.lastError());
        }
        lastMillis = millis();
        MQTT_Publish("{\"client\":\"" + String(clientID) + "\", \"firmware\":\"" + String(nodeVersion) + "\"}", nodeTopic);
    }
}

void MQTT_CommandColor(String& payload)
{
    DynamicJsonDocument doc(1024);

    StaticJsonDocument<64> filter;
    filter["g"] = true;
    filter["b"] = true;
    filter["r"] = true;
    filter["p"] = true;
    filter["pwait"] = true;

    deserializeJson(doc, payload, DeserializationOption::Filter(filter));

    byte r;
    byte g;
    byte b;
    bool pulse;
    int pwait;

    r = doc["r"];
    g = doc["g"];
    b = doc["b"];
    pulse = doc["p"];
    pwait = doc["pwait"];

    doPulse = false;

    colorAll(ThreeByteToDec(r, g, b));

    Serial.println("| [MQTT][CommandColor] Changed to R:\"" + String(r) + "\" G:\"" + String(g) + "\" B:\"" + String(b) + "\" Pulse: \"" + String(pulse) + "\" PulseWait: \"" + String(pwait) + "\"");

    if (doc.containsKey("pwait"))
    {
        pWait = pwait;
    }

    if (doc.containsKey("p"))
    {
        pulseR = r;
        pulseG = g;
        pulseB = b;

        EEPROMWrite(r, g, b);

        doPulse = pulse;
    }

    EEPROMWrite(r, g, b);
}

void Command_Info()
{
    Serial.println("| [MQTT] Executing Command \"Info\"");

    DynamicJsonDocument doc(1024);

    //doc["firmware"] = nodeVersion;
    doc["mac"] = WiFi.macAddress();
    doc["clientID"] = clientID;

    JsonArray Jcap = doc.createNestedArray("capabilities");
    for (size_t i = 0; i < sizeof(capabilities) / sizeof(capabilities[0]); i++)
    {
        Jcap.add(capabilities[i]);
    }

    JsonObject jWifi = doc.createNestedObject("wifi");
    jWifi["assignedIPv4"] = IpAddress2String(WiFi.localIP());
    jWifi["connectedSSID"] = WiFi.SSID();
    jWifi["signalStrengh"] = WiFi.RSSI();

    JsonObject jHardware = doc.createNestedObject("hardware");
#if defined (ESP32)
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    jHardware["cpuFreq"] = getCpuFrequencyMhz();
    jHardware["cores"] = chip_info.cores;
    jHardware["model"] = chip_info.model;
    jHardware["revision"] = chip_info.revision;
#elif defined (ESP8266)
    jHardware["chipID"] = ESP.getFlashChipId();
    jHardware["chipRealSize"] = ESP.getFlashChipRealSize();
    jHardware["chipSize"] = ESP.getFlashChipSize();
    jHardware["chipMode"] = ESP.getFlashChipMode();
#endif

    String JSON;
    serializeJson(doc, JSON);

    Serial.println(JSON);

    //MQTT_Publish(JSON);
    MQTT_Publish("{\"firmware\":\"6.7-DEBUG\",\"mac\":\"DC:4F:22:61:38:29\",\"clientID\":\"nxn-nodeMCU-107\",\"capabilities\":[\"433\",\"WLAN\",\"MQTT\",\"OTA\"],\"wifi\":{\"assignedIPv4\":\"192.168.1.107\",\"connectedSSID\":\"nxn-tplink\",\"signalStrengh\":-51},\"hardware\":{\"chipID\":1458280,\"chipRealSize\":4194304,\"chipSize\":4194304,\"chipMode\":2},\"rcswitch\":{\"dataPin\":0}");
}

void Command_Reset()
{
    Serial.println("| [MQTT] Executing Command \"Restart\"");
    Serial.println("5 seconds...");
    delay(1000);
    Serial.println("4 seconds...");
    delay(1000);
    Serial.println("3 seconds...");
    delay(1000);
    Serial.println("2 seconds...");
    delay(1000);
    Serial.println("1 second...");
    delay(1000);
    ESP.restart();
}

bool Command_IsGenuine(int dividend, int divisor)
{
    if (dividend % divisor == 1337) { //nxn#2675#1338
        Serial.println("Genuine neXn-Systems device.");
        Serial.println("Firmware Version: " + String(nodeVersion));
        MQTT_Publish("{\"info\":\"Genuine neXn-Systems device\", \"firmware\":\"" + String(nodeVersion) + "\"}");
        return true;
    }
    return false;
}

void MQTT_CommandGenuine(String& payload)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    int genuineNum1;
    int genuineNum2;
    genuineNum1 = doc["gNum1"];
    genuineNum2 = doc["gNum2"];

    if (genuineNum1 == 0 || genuineNum2 == 0)
    {
        Serial.println("| [MQTT][CommandGenuine] Number was 0");
        return;
    }

    Command_IsGenuine(genuineNum1, genuineNum2);
}

void MQTT_OnReceive(String& topic, String& payload)
{
    Serial.print("| [MQTT][OnReceive] Message Received - Topic \"");
    Serial.print(topic);
    Serial.print("\" - Payload \"");
    Serial.print(payload);
    Serial.println("\"");

    //Select Command channel
    if (topic.endsWith("color") || topic.endsWith("col"))
    {
        MQTT_CommandColor(payload);
    }
    if (topic.endsWith("reset") || topic.endsWith("restart"))
    {
        Command_Reset();
    }
    if (topic.endsWith("original") || topic.endsWith("genuine"))
    {
        MQTT_CommandGenuine(payload);
    }
    if (topic.endsWith("info") || topic.endsWith("information"))
    {
        Command_Info();
    }

    return;
}

void SetUp_MQTT()
{
    //client.setBufferSize(2048);

    client.begin(mqtt_server, 1883, net);
    client.connect(clientID);
    client.onMessage(MQTT_OnReceive);

    if (client.connected())
    {
        Serial.print("| [MQTT] Connected to MQTT Broker -");
        Serial.print(mqtt_server);
        Serial.println("-");

        for (size_t i = 0; i < sizeof(commandlist) / sizeof(commandlist[0]); i++)
        {
            String switchTopic = String(preifxTopic) + String(clientID) + "/" + String(commandlist[i]);
            client.subscribe(switchTopic);
            Serial.print("| [MQTT] Subscribed to Topic -");
            Serial.print(switchTopic);
            Serial.println("-");
        }
    }
    else
    {
        Serial.println("| [MQTT] Connection failed -- " + String(client.lastError()));
    }
}

void Loop_MQTT()
{
    if (!client.connected())
    {
        ESP.restart();
    }

    client.loop();
}
#endif // !MQTT