#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>
#include <Hardware/Button/ButtonDriver.h>

LiftCommandScheduler scheduler;
LiftManager liftManager(&scheduler);
WebSocketHandler webSocketHandler(&scheduler);
ButtonDriver floorButton(9);

void setup()
{
  Serial.begin(9600);

  webSocketHandler.begin();

  floorButton.onPress([]() {
    Serial.println("Button pressed");
    // scheduler.enqueue( CommandFactory::createCommand(...) );
  });
}

void loop()
{
  webSocketHandler.update();
  liftManager.update();
  floorButton.update();
}
