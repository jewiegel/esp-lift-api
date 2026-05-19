#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/LiftManager.h>
#include <Hardware/Button/ButtonDriver.h>
#include <Hardware/Led/LedDriver.h>

LiftCommandScheduler scheduler;
WebSocketHandler webSocketHandler(&scheduler);
ButtonDriver floorButton(4);

LedDriver led0(5), led1(6), led2(7), led3(15);
ILedDriver* floorLeds[] = { &led0, &led1, &led2, &led3 };

LiftManager liftManager(&scheduler, &webSocketHandler, &floorButton, floorLeds, 4);

void setup()
{
  Serial.begin(9600);

  webSocketHandler.begin();
}

void loop()
{
  webSocketHandler.update();
  liftManager.update();
}
