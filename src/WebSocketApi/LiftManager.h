#pragma once

#include "WebSocketHandler.h"
#include "LiftCommandScheduler.h"
#include <ArduinoJson.h>
#include "Hardware/Button/ButtonDriver.h"
#include "Hardware/Led/ILedDriver.h"

class LiftManager
{
private:
    LiftCommandScheduler *scheduler;
    WebSocketHandler *webSocketHandler;
    ButtonDriver *floorButton;
    ILedDriver **floorLeds;
    int ledCount;
    int currentLedIndex = 0;
    void onFloorButtonPress();
public:
    LiftManager(LiftCommandScheduler *scheduler, WebSocketHandler *webSocketHandler, ButtonDriver *floorButton, ILedDriver **floorLeds, int ledCount);
    ~LiftManager();
    void enqueueCommand(ICommand* command);
    void update();
    void commandCompleted();
    void clearCommands();
};