#include "neXn.WiFi.h"

neXnWiFi::neXnWiFi()
{
}

neXnWiFi::neXnWiFi(char* ssid, char* password, char* hostname)
{
    WiFi_SSID = ssid;
    WiFi_Password = password;
    WiFi_Hostname = hostname;
}

neXnWiFi::neXnWiFi(char* ssid, char* password, char* hostname, neXnWiFiConfig& config)
{
    WiFi_SSID = ssid;
    WiFi_Password = password;
    WiFi_Hostname = hostname;
    configure = config;
}

neXnWiFi::~neXnWiFi()
{
    WiFi.disconnect();
}

void neXnWiFi::Begin()
{
    Serial.printf("| [WiFi] Connecting to %s ", WiFi_SSID);
    WiFi.disconnect(true);
    delay(500);
    WiFi.mode(WIFI_STA);
    WiFi.config(configure.WiFi_IPA, configure.WiFi_DNSServerA, configure.WiFi_GatewayA, configure.WiFi_SubnetA);
    WiFi.setAutoReconnect(true);
    delay(500);
    WiFi.begin(WiFi_SSID, WiFi_Password);
#if defined(ESP32)
    WiFi.setHostname(WiFi_Hostname); //Set Hostname AFTER WiFi.begin();
#elif defined(ESP8266)
    WiFi.hostname(WiFi_Hostname); //Set Hostname AFTER WiFi.begin();
#endif
    WiFiConnect();

    Serial.println("| [NodeInfo] Node MAC: " + WiFi.macAddress());
    Serial.print("| [NodeInfo] Node IP: ");
    Serial.println(configure.WiFi_IPA);
    Serial.print("| [NodeInfo] Node Subnet: ");
    Serial.println(WiFi.subnetMask());

    //net = WiFi.Client;
}

void neXnWiFi::WiFiConnect()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        wifiRetries++;
        if (wifiRetries >= 20)
        {
            ESP.restart();
        }
    }
    Serial.println(" connected");
    wifiRetries = 0;
}

void neXnWiFi::WiFiReconnect()
{
    WiFi.reconnect();
    WiFiConnect();
}

void neXnWiFi::Handle()
{
    int wifistat = WiFi.status();
    if (wifistat == WL_DISCONNECTED || wifistat == WL_CONNECTION_LOST)
    {
        WiFiReconnect();
    }
}