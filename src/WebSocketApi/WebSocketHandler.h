#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class WebSocketHandler
{
private:
    AsyncWebServer *webServer;
    AsyncWebSocket *webSocket;
    String wifi_ssd = "FMI ImProvia Guest";
    String wifi_password = "Welcomeguest!";
    int port;
public:
    WebSocketHandler();
    ~WebSocketHandler();
    void begin();
    void update();
    void handleClient();
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void sendData(const char* data, ...);
};

