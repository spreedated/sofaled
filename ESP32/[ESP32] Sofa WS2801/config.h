#ifndef _CONFIG_H
#define _CONFIG_H

//Node Information
#if defined (_DEBUG)
const char* nodeVersion = "1.5-DEBUG";
#else
const char* nodeVersion = "1.5";
#endif

//#define ENABLE_OTA
#define ENABLE_WIFI
#define ENABLE_BLUETOOTH
#define ENABLE_SERIAL
#define ENABLE_WS2801
#define ENABLE_DS18B20

//Serial
const ulong SERIAL_BAUD = 115200;
//# ### #

// WiFi
const char* WiFi_SSID = "nxn-tplink";
const char* WiFi_Password = "04158063270538213808";
const char* WiFi_Hostname = "nxn-nodeMCU-90";
const String WiFi_IP = "192.168.1.90";
const String WiFi_DNSServer = "192.168.1.254";
const String WiFi_Gateway = "192.168.1.254";
const String WiFi_Subnet = "255.255.240.0";
//# ### #

//MQTT
const char* mqtt_server = "192.168.1.106";
const char* preifxTopic = "/neXn/sofa/";
const char* nodeTopic = "/neXn/sofa/nodes/";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* clientID = "nxn-nodeMCU-90";
const char* capabilities[] = { "433", "WLAN", "MQTT", "OTA" };
const char* commandlist[] = { "reset", "restart", "genuine", "original", "info", "information", "color"};
//# ### #

//ArduinoOTA
const int otaPort = 3232;
const char* otaPassword = "";
const char* otaMD5Password = "1c9fcae7146273d7443f5b7eac02d56d";
//# ### #

//WS2801 Strip
const int PixelCount = 160;
const uint8_t dataPin = 23;    // Yellow wire on Adafruit Pixels
const uint8_t clockPin = 22;    // Green wire on Adafruit Pixels
//# ### #

//Bluetooth
const char* BLUETOOTH_NAME = "Sofa LED";
//# ### #

//Temperature Sensor
const int ONE_WIRE_BUS = 12;
const float SHUTDOWN_TEMP_C = 45.0f;
//# ### #

#endif // !CONFIG_H
