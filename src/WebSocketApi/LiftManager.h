#pragma once

#include "WebSocketHandler.h"
#include "LiftCommandScheduler.h"

class LiftManager
{
private:
    LiftCommandScheduler *scheduler;
public:
    LiftManager(LiftCommandScheduler *scheduler);
    ~LiftManager();
    void enqueueCommand(ICommand* command);
    void update();
    void commandCompleted();
    void clearCommands();
};