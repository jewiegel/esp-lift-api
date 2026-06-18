#pragma once

#include "Commands/ICommand.h"
#include "CommandRegistry.h"
#include <deque>

class LiftCommandScheduler
{
private:
    std::deque<ICommand*> commandQueue;
    bool busy = false;
    ILiftCommandHandler* activeHandler = nullptr;
    int activeFloor = -1;

    bool isFloorAlreadyQueued(int floor) const;
public:
    LiftCommandScheduler();
    ~LiftCommandScheduler();
    void enqueue(ICommand* command);
    void processNext();
    void commandCompleted();
    void clearCommands();
    bool hasPendingCommands() const { return !commandQueue.empty(); }
    int pendingCommandCount() const { return commandQueue.size(); }
};
