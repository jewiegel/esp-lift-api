#include "RequestLiftHandler.h"
#include "../WebSocketHandler.h"

RequestLiftHandler::RequestLiftHandler(LiftController* controller, WebSocketHandler* wsHandler)
    : controller(controller), wsHandler(wsHandler)
{
}

RequestLiftHandler::~RequestLiftHandler()
{
}

void RequestLiftHandler::execute(const ICommand& command, std::function<void()> onCompleted)
{
    const RequestLiftCommand& liftCommand = static_cast<const RequestLiftCommand&>(command);
    targetFloor = liftCommand.getCurrentFloor();
    this->onCompleted = onCompleted;
    arrivedAnnounced = false;
    controller->moveToFloor(targetFloor);
    Serial.println("Lift requested at floor: " + String(targetFloor));
}

void RequestLiftHandler::update()
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

    // A robot must still board/leave here — hold until it is ready. Checked at the
    // controller level, so it holds regardless of which command brought the lift here.
    if (controller->isWaitingForRobotHere())
        return;

    onCompleted();
}
