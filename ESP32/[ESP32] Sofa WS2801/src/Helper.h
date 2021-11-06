#ifndef _HELPER_H
#define _HELPER_H

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") + \
        String(ipAddress[1]) + String(".") + \
        String(ipAddress[2]) + String(".") + \
        String(ipAddress[3]);
}
unsigned long interval = 3600000;
void RestartIfNecessary()
{
    if (millis() >= interval && ESP.getHeapSize() <= 5)
    {
        Serial.println("| [SYS] Restarting...");
        Serial.println("| [SYS] Heapsize: \"" + String(ESP.getHeapSize()) + "\"");
        ESP.restart();
    }
}
bool KeyWordComparison(const char* haystack[], int sizeOfHaystack, const char* needle)
{
    for (int x = 0; x < sizeOfHaystack; x++)
    {
        if (String(haystack[x]) == "all" || String(needle) == String(haystack[x]))
        {
            return true;
        }
    }
    return false;
}
// Create a 24 bit color value from R,G,B
uint32_t ThreeByteToDec(byte r, byte g, byte b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}
byte* DecToThreeByte(uint32_t dec)
{
    byte* c;
    c[0] = dec >> 16;
    c[1] = (dec / 256) & 255;
    c[2] = dec & 255;

    return c;
}

#endif // !HELPER