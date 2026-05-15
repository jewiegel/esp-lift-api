#include "RequestLiftHandler.h"

RequestLiftHandler::RequestLiftHandler()
{
}

RequestLiftHandler::~RequestLiftHandler()
{
}

void RequestLiftHandler::execute(const ICommand &command, std::function<void()> onCompleted)
{
    const RequestLiftCommand &liftCommand = static_cast<const RequestLiftCommand&>(command);

    Serial.println("Lift requested at floor: " + String(liftCommand.getCurrentFloor()) + " — arriving in 5s");
    this->onCompleted = onCompleted;
    endTime = millis() + 5000;
}

void RequestLiftHandler::update()
{
    if (endTime > 0 && millis() >= endTime) {
        endTime = 0;
        Serial.println("Lift arrived");
        onCompleted();
    }
}
