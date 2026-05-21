#include "WebSocketHandler.h"

WebSocketHandler::WebSocketHandler(LiftCommandScheduler *scheduler)
{
    this->port = 80;
    this->scheduler = scheduler;
    webServer = new AsyncWebServer(port);
    webSocket = new AsyncWebSocket("/ws");
}

WebSocketHandler::~WebSocketHandler()
{
    delete webServer;
    delete webSocket;
}

void WebSocketHandler::begin()
{
    WiFi.begin(wifi_ssd, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    webServer->begin();

    webSocket->onEvent(std::bind(&WebSocketHandler::onEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    webServer->addHandler(webSocket);
}

void WebSocketHandler::handleClient()
{
    Serial.println("WebSocket client connected");
}

void WebSocketHandler::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT) 
    {
        handleClient();
    } 
    else if (type == WS_EVT_DISCONNECT) 
    {
        Serial.println("WebSocket client disconnected");
    } 
    else if (type == WS_EVT_DATA) 
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, data, len);
        if (error) 
        {
            Serial.println("Failed to parse JSON");
            return;
        }
        
        ICommand* command = CommandFactory::createCommand(doc);
        if (!command) { Serial.println("Unknown command"); return; }

        scheduler->enqueue(command);
    }
}

void WebSocketHandler::sendData(const JsonDocument& doc)
{
    String output;
    serializeJson(doc, output);
    webSocket->textAll(output);
}

void WebSocketHandler::update()
{
    webSocket->cleanupClients();
}
