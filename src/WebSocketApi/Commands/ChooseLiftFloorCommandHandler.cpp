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
    arrivedAnnounced = false;
    controller->moveToFloor(targetFloor);
    Serial.println("Lift moving to floor: " + String(targetFloor));
}

void ChooseLiftFloorCommandHandler::update()
{
    // Not arrived yet
    if (controller->getCurrentFloor() != targetFloor || !controller->areDoorsOpen())
        return;

    // Announce arrival once
    if (!arrivedAnnounced)
    {
        arrivedAnnounced = true;
        JsonDocument doc;
        doc["event"] = "liftArrived";
        doc["floor"] = targetFloor;
        wsHandler->sendData(doc);
    }

    // A robot must still board/leave here — hold until it is ready
    if (controller->isWaitingForRobotHere())
        return;

    onCompleted();
}