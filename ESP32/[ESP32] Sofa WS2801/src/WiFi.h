#ifndef _WIFI_H
#define _WIFI_H

    #if defined (ENABLE_WIFI)
        #if defined(ESP32)
            //#include <WiFiUdp.h>
            //#include <WiFiType.h>
            //#include <WiFiSTA.h>
            //#include <WiFiServer.h>
            //#include <WiFiScan.h>
            //#include <WiFiMulti.h>
            //#include <WiFiGeneric.h>
            #include <WiFiClient.h>
            //#include <WiFiAP.h>
            #include <WiFi.h>
            //#include <ETH.h>
        #else
            #include <ESP8266WiFi.h>
            #include <WiFiUDP.h>
        #endif

        //IPAddress from String
        const IPAddress WiFi_IPA = IPAddress(SplitStringValue(WiFi_IP, '.', 0).toInt(), SplitStringValue(WiFi_IP, '.', 1).toInt(), SplitStringValue(WiFi_IP, '.', 2).toInt(), SplitStringValue(WiFi_IP, '.', 3).toInt());
        const IPAddress WiFi_DNSServerA = IPAddress(SplitStringValue(WiFi_DNSServer, '.', 0).toInt(), SplitStringValue(WiFi_DNSServer, '.', 1).toInt(), SplitStringValue(WiFi_DNSServer, '.', 2).toInt(), SplitStringValue(WiFi_DNSServer, '.', 3).toInt());
        const IPAddress WiFi_GatewayA = IPAddress(SplitStringValue(WiFi_Gateway, '.', 0).toInt(), SplitStringValue(WiFi_Gateway, '.', 1).toInt(), SplitStringValue(WiFi_Gateway, '.', 2).toInt(), SplitStringValue(WiFi_Gateway, '.', 3).toInt());
        const IPAddress WiFi_SubnetA = IPAddress(SplitStringValue(WiFi_Subnet, '.', 0).toInt(), SplitStringValue(WiFi_Subnet, '.', 1).toInt(), SplitStringValue(WiFi_Subnet, '.', 2).toInt(), SplitStringValue(WiFi_Subnet, '.', 3).toInt());

        int wifiRetries = 0;
        void WiFiConnect()
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

        void WiFiReconnect()
        {
            WiFi.reconnect();
            WiFiConnect();
        }

        void SetUp_WiFi()
        {
            Serial.printf("| [WiFi] Connecting to %s ", WiFi_SSID);
            WiFi.mode(WIFI_STA);
            WiFi.config(WiFi_IPA, WiFi_DNSServerA, WiFi_GatewayA, WiFi_SubnetA);
            WiFi.setAutoReconnect(true);
            WiFi.begin(WiFi_SSID, WiFi_Password);
        #if defined(ESP32)
            WiFi.setHostname(WiFi_Hostname); //Set Hostname AFTER WiFi.begin();
        #elif defined(ESP8266)
            WiFi.hostname(WiFi_Hostname); //Set Hostname AFTER WiFi.begin();
        #endif
            WiFiConnect();

            Serial.print("Welcome to the neXn-Systems NodeMCU v");
            Serial.println(nodeVersion);
            Serial.println("| [NodeInfo] Node MAC: " + WiFi.macAddress());
            Serial.println("| [NodeInfo] Node IP: " + WiFi_IP);
        }

        void Loop_WiFi()
        {
            int wifistat = WiFi.status();
            if (wifistat == WL_DISCONNECTED || wifistat == WL_CONNECTION_LOST)
            {
                WiFiReconnect();
            }
        }
    #endif
#endif // !WIFI