#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>
#include <Hardware/Button/ButtonDriver.h>
#include <Hardware/Led/LedDriver.h>
#include <Lift/LiftController.h>

LiftCommandScheduler scheduler;
WebSocketHandler webSocketHandler(&scheduler);

LiftController liftController;

void setup()
{
  Serial.begin(9600);

  webSocketHandler.begin();
  liftController.setup();
}

void loop()
{
  webSocketHandler.update();
  //liftManager.update();
  liftController.update();
}
