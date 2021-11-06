#ifndef _NEXNMQTT_H
#define _NEXNMQTT_H

#include <ArduinoJson.h>
#include <MQTTClient.h>
#include <MQTT.h>
#include <WiFiClient.h>

class neXnMQTT
{
public:
	neXnMQTT();
	neXnMQTT(String serverIP, String clientId, WiFiClient wifiClient, int port);
	~neXnMQTT();
	void Begin(char* subscriptionTopics[]);
	void Handle();
	void Publish(String msg, const char* topic);
private:
	String serverIP;
	String clientId;
	int port;
	WiFiClient net;
	unsigned long lastMillis = 0;
	unsigned long pushIntervalAliveMessage;
	MQTTClient client;
	void PublishAlive();
    static void OnReceive(String& topic, String& payload);
};

#endif // !_NEXNMQTT_H