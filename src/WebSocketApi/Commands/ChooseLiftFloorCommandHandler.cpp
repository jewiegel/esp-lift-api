#include "ChooseLiftFloorCommandHandler.h"
#include "../WebSocketHandler.h"

ChooseLiftFloorCommandHandler::ChooseLiftFloorCommandHandler(LiftController* controller, WebSocketHandler* wsHandler)
    : controller(controller), wsHandler(wsHandler)
{
}

ChooseLiftFloorCommandHandler::~ChooseLiftFloorCommandHandler()
{
}

void ChooseLiftFloorCommandHandler::execute(const ICommand& command, std::function<void()> onCompleted)
{
    const ChooseLiftFloorCommand& floorCommand = static_cast<const ChooseLiftFloorCommand&>(command);
    targetFloor = floorCommand.getFloor();
    this->onCompleted = onCompleted;
    controller->goToFloor(targetFloor);
    Serial.println("Lift moving to floor: " + String(targetFloor));
}

void ChooseLiftFloorCommandHandler::update()
{
    if (controller->getCurrentFloor() == targetFloor && controller->areDoorsOpen()) {
        JsonDocument doc;
        doc["event"] = "floorReached";
        doc["floor"] = targetFloor;
        wsHandler->sendData(doc);
        onCompleted();
    }
}