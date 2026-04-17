#include <WebSocketApi/WebSocketHandler.h>

WebSocketHandler::WebSocketHandler()
{
    this->port = 80;
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
        Serial.printf("Received data: %.*s\n", len, data);
        sendData("Message received: %.*s\n", len, data);
    }
}

void WebSocketHandler::sendData(const char* format, ...)
{
    char buffer[256]; // Zorg dat deze groot genoeg is
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    webSocket->textAll(buffer);
}

void WebSocketHandler::update()
{
    webSocket->cleanupClients();

    // Voorbeeld: Stuur elke 5 sec data naar alle clients
    static unsigned long lastTime = 0;
    if (millis() - lastTime > 5000) {
        lastTime = millis();
        String uptime = "Uptime: " + String(millis() / 1000) + "s";
        webSocket->textAll(uptime);
    }
}
