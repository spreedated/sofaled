#include "neXnMQTT.h"

neXnMQTT::neXnMQTT()
{
}

neXnMQTT::neXnMQTT(String serverIP, String clientId, WiFiClient wifiClient, int port = 1883)
{
    neXnMQTT::serverIP = serverIP;
    neXnMQTT::port = port;
    neXnMQTT::clientId = clientId;
    net = wifiClient;
}

neXnMQTT::~neXnMQTT()
{
    client.~MQTTClient();
}

void neXnMQTT::Begin(char* subscriptionTopics[])
{
    //client.setBufferSize(2048);
    
    client.begin(serverIP.c_str(), port, net);
    client.connect(clientId.c_str());
    client.onMessage(OnReceive);

    if (client.connected())
    {
        Serial.print("| [MQTT] Connected to MQTT Broker -");
        Serial.print(serverIP);
        Serial.println("-");

        for (size_t i = 0; i < sizeof(subscriptionTopics) / sizeof(subscriptionTopics[0]); i++)
        {
            String switchTopic = String(subscriptionTopics[i]);
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

void neXnMQTT::Handle()
{
    if (!client.connected())
    {
        ESP.restart();
    }
    client.loop();
}

void neXnMQTT::OnReceive(String& topic, String& payload)
{
    Serial.print("| [MQTT][OnReceive] Message Received - Topic \"");
    Serial.print(topic);
    Serial.print("\" - Payload \"");
    Serial.print(payload);
    Serial.println("\"");

    //Select Command channel
    /*if (topic.endsWith("color") || topic.endsWith("col"))
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
    }*/

    return;
}

void neXnMQTT::Publish(String msg, const char* topic = NULL)
{
    if (!client.publish(topic, msg, false, 0))
    {
        client.connect(clientId.c_str());
        delay(10);
        client.publish(topic, msg, false, 0);
    }
}

void neXnMQTT::PublishAlive()
{
    if (millis() - lastMillis > pushIntervalAliveMessage) {
        if (!client.connected()) {
            Serial.print("| [MQTT] LastError: ");
            Serial.println(client.lastError());
        }
        lastMillis = millis();

        //Publish("{\"client\":\"" + String(clientId) + "\", \"firmware\":\"N/A\"}", nodeTopic);
    }
}