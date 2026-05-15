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
    // Handle incoming WebSocket clients
}

void WebSocketHandler::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT) {
        Serial.println("WebSocket client connected");
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("WebSocket client disconnected");
    } else if (type == WS_EVT_DATA) {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, data, len);
        if (error) {
            Serial.println("Failed to parse JSON");
            return;
        }
        
        ICommand* command = CommandFactory::createCommand(doc);
        if (!command) { Serial.println("Unknown command"); return; }

        ILiftCommandHandler* handler = CommandRegistry::convertHandler(command->getName());
        if (handler) {
            handler->execute(*command);
        } else {
            Serial.println("No handler found for command: " + command->getName());
        }
    }
}

void WebSocketHandler::sendData(const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    webSocket->textAll(buffer);
}

void WebSocketHandler::update()
{
    webSocket->cleanupClients();

    static unsigned long lastTime = 0;
    if (millis() - lastTime > 5000) {
        lastTime = millis();
        String uptime = "Uptime: " + String(millis() / 1000) + "s";
        webSocket->textAll(uptime);
    }
}
