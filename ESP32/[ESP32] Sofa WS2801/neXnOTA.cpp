#include "neXnOTA.h"

neXnOTA::neXnOTA(uint16_t port, const char* hostname)
{
    neXnOTA::port = port;
    neXnOTA::hostname = hostname;
}

neXnOTA::neXnOTA(uint16_t port, const char* hostname, const char* password, bool isMD5Hashed = false)
{
    neXnOTA::port = port;
    neXnOTA::hostname = hostname;
    if (isMD5Hashed)
    {
        neXnOTA::password_md5 = password_md5;
    }
    else
    {
        neXnOTA::password = password;
    }
}

neXnOTA::~neXnOTA()
{

}

void neXnOTA::Begin()
{
    ArduinoOTA.setPort(port);
    ArduinoOTA.setHostname(hostname);
    if (strlen(password_md5) > 0)
    {
        ArduinoOTA.setPasswordHash(password_md5);
    }
    else if (strlen(password) > 0)
    {
        ArduinoOTA.setPassword(password);
    }
}

void neXnOTA::Start()
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
