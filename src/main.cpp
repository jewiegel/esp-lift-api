#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>

LiftCommandScheduler scheduler;
WebSocketHandler webSocketHandler(&scheduler);

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello, World!");

  webSocketHandler.begin();
}

void loop()
{
  webSocketHandler.update();
}
