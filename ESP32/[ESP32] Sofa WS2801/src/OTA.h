#ifndef _OTA_H
#define _OTA_H

#if defined (ENABLE_OTA)
    #include <ArduinoOTA.h>

    void StartOTA()
    {
        ArduinoOTA.onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("| [OTA] Start updating " + type);
            });

        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("| [OTA] Progress: %u%%\n", (progress / (total / 100)));
            });

        ArduinoOTA.onError([](ota_error_t error) {
            Serial.printf("| [OTA] Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) Serial.println("End Failed");

            });

        ArduinoOTA.onEnd([]() {
            Serial.println("\n| [OTA] End");
            });

        ArduinoOTA.begin();

        Serial.println("| [OTA] Ready!");
    }

    void SetUp_OTA()
    {
        ArduinoOTA.setPort(otaPort);
        ArduinoOTA.setHostname(clientID);
        if (strlen(otaMD5Password) > 0)
        {
            ArduinoOTA.setPasswordHash(otaMD5Password);
        }
        else if (strlen(otaPassword) > 0)
        {
            ArduinoOTA.setPassword(otaPassword);
        }
        StartOTA();
    }
    #endif
#endif // !OTA