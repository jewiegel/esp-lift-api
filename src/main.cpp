#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>

WebSocketHandler webSocketHandler;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");

  webSocketHandler.begin();
}

void loop() {
  webSocketHandler.update();
}
