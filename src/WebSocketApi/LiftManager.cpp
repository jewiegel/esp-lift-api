#include "LiftManager.h"

LiftManager::LiftManager(LiftCommandScheduler *scheduler) : scheduler(scheduler)
{
}

LiftManager::~LiftManager()
{
}

void LiftManager::enqueueCommand(ICommand* command)
{
    scheduler->enqueue(command);
}

void LiftManager::update()
{
    scheduler->processNext();
}

void LiftManager::commandCompleted()
{
    scheduler->commandCompleted();
}

void LiftManager::clearCommands()
{
    // Clear all commands from the scheduler
}