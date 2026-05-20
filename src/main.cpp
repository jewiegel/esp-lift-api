#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>
#include <Hardware/Button/ButtonDriver.h>
#include <Hardware/Led/LedDriver.h>
#include <Lift/LiftController.h>

LiftCommandScheduler scheduler;
WebSocketHandler webSocketHandler(&scheduler);

LiftController liftController;
IButtonDriver* switchDriver = new ButtonDriver(19);

void setup()
{
  Serial.begin(9600);

  webSocketHandler.begin();
  liftController.setup();

  switchDriver->onPress([]() {
    Serial.println("Switch triggered! Enqueuing lift command to floor 2.");
  });
}

void loop()
{
  webSocketHandler.update();
  //liftManager.update();
  liftController.update();
  switchDriver->update();
}
