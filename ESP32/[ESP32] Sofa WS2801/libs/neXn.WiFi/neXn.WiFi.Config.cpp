#include "neXn.WiFi.Config.h"

String neXnWiFiConfig::SplitStringValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void neXnWiFiConfig::StringsToIPv4()
{
	WiFi_IPA = IPAddress(SplitStringValue(WiFi_IP, '.', 0).toInt(), SplitStringValue(WiFi_IP, '.', 1).toInt(), SplitStringValue(WiFi_IP, '.', 2).toInt(), SplitStringValue(WiFi_IP, '.', 3).toInt());
	WiFi_DNSServerA = IPAddress(SplitStringValue(WiFi_DNSServer, '.', 0).toInt(), SplitStringValue(WiFi_DNSServer, '.', 1).toInt(), SplitStringValue(WiFi_DNSServer, '.', 2).toInt(), SplitStringValue(WiFi_DNSServer, '.', 3).toInt());
	WiFi_GatewayA = IPAddress(SplitStringValue(WiFi_Gateway, '.', 0).toInt(), SplitStringValue(WiFi_Gateway, '.', 1).toInt(), SplitStringValue(WiFi_Gateway, '.', 2).toInt(), SplitStringValue(WiFi_Gateway, '.', 3).toInt());
	WiFi_SubnetA = IPAddress(SplitStringValue(WiFi_Subnet, '.', 0).toInt(), SplitStringValue(WiFi_Subnet, '.', 1).toInt(), SplitStringValue(WiFi_Subnet, '.', 2).toInt(), SplitStringValue(WiFi_Subnet, '.', 3).toInt());
}

neXnWiFiConfig::neXnWiFiConfig(String ip, String dns, String gateway, String subnet)
{
    WiFi_IP = ip;
    WiFi_DNSServer = dns;
    WiFi_Gateway = gateway;
    WiFi_Subnet = subnet;

    StringsToIPv4();
}

neXnWiFiConfig::neXnWiFiConfig()
{
}