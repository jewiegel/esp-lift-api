#pragma once

#include "WebSocketHandler.h"
#include "LiftCommandScheduler.h"
#include "Lift/LiftController.h"
#include <ArduinoJson.h>

class LiftManager
{
private:
    LiftCommandScheduler *scheduler;
    WebSocketHandler *webSocketHandler;
    LiftController *liftController;
    int ledCount;
    int currentLedIndex = 0;
    void onFloorButtonPress();
public:
    LiftManager(LiftCommandScheduler *scheduler, WebSocketHandler *webSocketHandler, LiftController *liftController);
    ~LiftManager();
    void enqueueCommand(ICommand* command);
    void update();
    void commandCompleted();
    void clearCommands();
};