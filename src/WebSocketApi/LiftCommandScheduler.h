#pragma once

#include "Commands/ICommand.h"
#include "CommandRegistry.h"
#include <queue>

class LiftCommandScheduler
{
private:
    std::queue<ICommand*> commandQueue;
    bool busy = false;
    ILiftCommandHandler* activeHandler = nullptr;
public:
    LiftCommandScheduler();
    ~LiftCommandScheduler();
    void enqueue(ICommand* command);
    void processNext();
    void commandCompleted();
    void clearCommands();
};
