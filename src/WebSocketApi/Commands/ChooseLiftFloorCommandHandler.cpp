#include "ChooseLiftFloorCommandHandler.h"

ChooseLiftFloorCommandHandler::ChooseLiftFloorCommandHandler()
{
}

ChooseLiftFloorCommandHandler::~ChooseLiftFloorCommandHandler()
{
}

void ChooseLiftFloorCommandHandler::execute(const ICommand &command, std::function<void()> onCompleted)
{
    const ChooseLiftFloorCommand &floorCommand = static_cast<const ChooseLiftFloorCommand&>(command);

    Serial.println("Lift moving to floor: " + String(floorCommand.getFloor()) + " — arriving in 5s");
    this->onCompleted = onCompleted;
    endTime = millis() + 5000;
}

void ChooseLiftFloorCommandHandler::update()
{
    if (endTime > 0 && millis() >= endTime) {
        endTime = 0;
        Serial.println("Lift arrived at floor");
        onCompleted();
    }
}