#ifndef _NEXNWIFI_CONFIG_H
#define _NEXNWIFI_CONFIG_H

#include <Arduino.h>

class neXnWiFiConfig
{
private:
	String WiFi_IP;
	String WiFi_DNSServer;
	String WiFi_Gateway;
	String WiFi_Subnet;
	void StringsToIPv4();
	String SplitStringValue(String data, char separator, int index);
public:
	IPAddress WiFi_IPA;
	IPAddress WiFi_DNSServerA;
	IPAddress WiFi_GatewayA;
	IPAddress WiFi_SubnetA;
	neXnWiFiConfig();
	neXnWiFiConfig(String ip, String dns, String gateway, String subnet);
};

#endif // !NEXNWIFI_CONFIG