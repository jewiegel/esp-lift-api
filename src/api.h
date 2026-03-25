#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <ArduinoJson.h>

class api
{
private:
    const char* wifi_ssd;
    const char* wifi_password;
    
public:
    api(const char* wifi_ssd, const char* wifi_password);
    bool connectToWiFi();
    WebServer* server;
    void getData();
    void setPins();
    
    ~api();
};
