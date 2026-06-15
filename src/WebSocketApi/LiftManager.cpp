#include "LiftManager.h"

LiftManager::LiftManager(LiftCommandScheduler *scheduler,
    WebSocketHandler *webSocketHandler,
    LiftController *liftController) : scheduler(scheduler),
    webSocketHandler(webSocketHandler),
    liftController(liftController)
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
    liftController->update();
}

void LiftManager::commandCompleted()
{
    scheduler->commandCompleted();
}

void LiftManager::clearCommands()
{
    scheduler->clearCommands();
}
