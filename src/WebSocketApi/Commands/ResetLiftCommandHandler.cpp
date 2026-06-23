#include "ResetLiftCommandHandler.h"
#include "../WebSocketHandler.h"

ResetLiftCommandHandler::ResetLiftCommandHandler(LiftController* controller, WebSocketHandler* wsHandler)
    : controller(controller), wsHandler(wsHandler)
{
}

ResetLiftCommandHandler::~ResetLiftCommandHandler()
{
}

void ResetLiftCommandHandler::execute(const ICommand& command, std::function<void()> onCompleted)
{
    this->onCompleted = onCompleted;
    controller->resetLift();
    Serial.println("Lift resetting to floor 0");
}

void ResetLiftCommandHandler::update()
{
    if (controller->getCurrentFloor() == 0 && !controller->areDoorsOpen()
        && !controller->areDoorsInMotion() && !controller->getIsMoving())
    {
        JsonDocument doc;
        doc["event"] = "liftReset";
        doc["floor"] = 0;
        wsHandler->sendData(doc);
        onCompleted();
    }
}
