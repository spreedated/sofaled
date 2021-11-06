#ifndef _NEXNOTA_H
#define _NEXNOTA_H

#include <ArduinoOTA.h>

class neXnOTA
{
public:
	neXnOTA(uint16_t port, const char* hostname);
	neXnOTA(uint16_t port, const char* hostname, const char* password, bool isMD5Hashed);
	~neXnOTA();
	void Begin();
private:
	uint16_t port;
	const char* hostname;
	const char* password;
	const char* password_md5;
	void Start();
};

#endif // !_NEXNOTA_H