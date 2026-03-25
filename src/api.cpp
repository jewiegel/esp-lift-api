#include <api.h>

api::api(const char* wifi_ssd, const char* wifi_password) {
    this->wifi_ssd = wifi_ssd;
    this->wifi_password = wifi_password;
}

bool api::connectToWiFi() {
    WiFi.begin(wifi_ssd, wifi_password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());
    server = new WebServer(80);

    server->on("/api/data", HTTP_GET, std::bind(&api::getData, this));
    server->on("/api/pins", HTTP_POST, std::bind(&api::setPins, this));
    server->begin();
    return true;
}

void api::getData() {
    StaticJsonDocument<200> doc;
    doc["message"] = "Hello, World!";
    String jsonString;
    serializeJson(doc, jsonString);
    server->send(200, "application/json", jsonString);
}

void api::setPins() {
    //read the request body
    String body = server->arg("plain");
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
        server->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }
    int pin = doc["pin"];
    int value = doc["value"];
    digitalWrite(pin, value);
    server->send(200, "application/json", "{\"status\":\"success\"}");
}