#include "StatusCommandHandler.h"
#include "../WebSocketHandler.h"
#include "../LiftCommandScheduler.h"

StatusCommandHandler::StatusCommandHandler(LiftController* controller, WebSocketHandler* wsHandler, LiftCommandScheduler* scheduler)
    : controller(controller), wsHandler(wsHandler), scheduler(scheduler)
{
}

StatusCommandHandler::~StatusCommandHandler()
{
}

void StatusCommandHandler::execute(const ICommand& command, std::function<void()> onCompleted)
{
    String doorStatus;
    if (controller->areDoorsInMotion())   doorStatus = "moving";
    else if (controller->areDoorsOpen())  doorStatus = "open";
    else                                  doorStatus = "closed";

    JsonDocument doc;
    doc["event"] = "status";
    doc["floor"] = controller->getCurrentFloor();
    doc["doors"] = doorStatus;
    doc["isMoving"] = controller->getIsMoving();
    doc["hasQueuedCommands"] = scheduler->hasPendingCommands();
    doc["queuedCommands"] = scheduler->pendingCommandCount();
    wsHandler->sendData(doc);

    Serial.println("Status sent");
    onCompleted();
}
