#include "LiftCommandScheduler.h"

LiftCommandScheduler::LiftCommandScheduler()
{
}

LiftCommandScheduler::~LiftCommandScheduler()
{
}

void LiftCommandScheduler::enqueue(ICommand* command)
{
    commandQueue.push(command);
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
    commandQueue.pop();

    activeHandler = CommandRegistry::convertHandler(command->getName());
    if (activeHandler) activeHandler->execute(*command, [this]() { commandCompleted(); });
    else commandCompleted();

    delete command;
}

void LiftCommandScheduler::commandCompleted()
{
    busy = false;
    activeHandler = nullptr;
}

void LiftCommandScheduler::clearCommands()
{
    while (!commandQueue.empty()) {
        ICommand* command = commandQueue.front();
        commandQueue.pop();
        delete command; // Clean up each command
    }
}
