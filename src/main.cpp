#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>
#include <WebSocketApi/CommandRegistry.h>
#include <Lift/LiftController.h>
#include "Hardware/Servo/ServoDriver.h"
#include "Hardware/Button/ButtonDriver.h"

LiftCommandScheduler scheduler;
WebSocketHandler webSocketHandler(&scheduler);
LiftController liftController(&scheduler);
LiftManager liftManager(&scheduler, &webSocketHandler, &liftController);

bool doorOpen = false;

void setup()
{
  Serial.begin(9600);

  CommandRegistry::init(&liftController, &webSocketHandler, &scheduler);
  webSocketHandler.begin();
  liftController.setup();
}

void loop()
{
  webSocketHandler.update();
  liftManager.update();
}
