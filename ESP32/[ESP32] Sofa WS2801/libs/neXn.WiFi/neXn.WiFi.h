#ifndef _NEXNWIFI_H
#define _NEXNWIFI_H

#if defined(ESP32)
	#include <WiFiUdp.h>
	#include <WiFiType.h>
	//#include <WiFiSTA.h>
	#include <WiFiServer.h>
	#include <WiFiScan.h>
	#include <WiFiMulti.h>
	#include <WiFiGeneric.h>
	#include <WiFiClient.h>
	#include <WiFiAP.h>
	#include <WiFi.h>
	#include <ETH.h>
#else
	#include <ESP8266WiFi.h>
	#include <WiFiUDP.h>
#endif

#include "neXn.WiFi.Config.h"

class neXnWiFi
{
private:
	void WiFiConnect();
	void WiFiReconnect();
	int wifiRetries = 0;
	char* WiFi_SSID;
	char* WiFi_Password;
	char* WiFi_Hostname;
	neXnWiFiConfig configure;
public:
	neXnWiFi();
	neXnWiFi(char* ssid, char* password, char* hostname);
	neXnWiFi(char* ssid, char* password, char* hostname, neXnWiFiConfig& config);
	~neXnWiFi();
	void Begin();
	void Handle();
	WiFiClient net;
};

#endif // !NEXNWIFI