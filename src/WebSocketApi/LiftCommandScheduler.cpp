#include "LiftCommandScheduler.h"

LiftCommandScheduler::LiftCommandScheduler()
{
}

LiftCommandScheduler::~LiftCommandScheduler()
{
}

bool LiftCommandScheduler::isFloorAlreadyQueued(int floor) const
{
    // Currently being served?
    if (floor == activeFloor) return true;

    // Already waiting in the queue?
    for (ICommand* queued : commandQueue)
    {
        if (queued->getTargetFloor() == floor) return true;
    }
    return false;
}

void LiftCommandScheduler::enqueue(ICommand* command)
{
    int floor = command->getTargetFloor();

    // Drop duplicate floor requests. The waitForRobot status is registered on the
    // controller at receipt (before enqueue), so it is preserved even when the
    // redundant movement command is discarded here.
    if (floor >= 0 && isFloorAlreadyQueued(floor))
    {
        delete command;
        return;
    }

    commandQueue.push_back(command);
}

void LiftCommandScheduler::processNext()
{
    if (busy) {
        if (activeHandler) activeHandler->update();
        return;
    }
    if (commandQueue.empty()) return;

    busy = true;
    ICommand* command = commandQueue.front();
    commandQueue.pop_front();
    activeFloor = command->getTargetFloor();

    activeHandler = CommandRegistry::convertHandler(command->getName());
    if (activeHandler) activeHandler->execute(*command, [this]() { commandCompleted(); });
    else commandCompleted();

    delete command;
}

void LiftCommandScheduler::commandCompleted()
{
    busy = false;
    activeHandler = nullptr;
    activeFloor = -1;
}

void LiftCommandScheduler::clearCommands()
{
    while (!commandQueue.empty()) {
        ICommand* command = commandQueue.front();
        commandQueue.pop_front();
        delete command; // Clean up each command
    }
}
