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
    controller->goToFloor(targetFloor);
    Serial.println("Lift requested at floor: " + String(targetFloor));
}

void RequestLiftHandler::update()
{
    if (controller->getCurrentFloor() == targetFloor && controller->areDoorsOpen()) 
    {
        JsonDocument doc;
        doc["event"] = "liftArrived";
        doc["floor"] = targetFloor;
        wsHandler->sendData(doc);
        onCompleted();
    }
}
