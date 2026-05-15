#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>

LiftCommandScheduler scheduler;
LiftManager liftManager(&scheduler);
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
  liftManager.update();
}
