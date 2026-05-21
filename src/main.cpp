#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>
#include <WebSocketApi/CommandRegistry.h>
#include <Lift/LiftController.h>

LiftCommandScheduler scheduler;
WebSocketHandler webSocketHandler(&scheduler);
LiftController liftController;
LiftManager liftManager(&scheduler, &webSocketHandler, &liftController);

void setup()
{
  Serial.begin(9600);

  CommandRegistry::init(&liftController, &webSocketHandler);
  webSocketHandler.begin();
  liftController.setup();
}

void loop()
{
  webSocketHandler.update();
  liftManager.update();
}
