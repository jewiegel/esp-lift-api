#include "ChooseLiftFloorCommandHandler.h"

ChooseLiftFloorCommandHandler::ChooseLiftFloorCommandHandler()
{
}

ChooseLiftFloorCommandHandler::~ChooseLiftFloorCommandHandler()
{
}

void ChooseLiftFloorCommandHandler::execute(const ICommand &command)
{
    const ChooseLiftFloorCommand &liftCommand = static_cast<const ChooseLiftFloorCommand&>(command);

    Serial.println("Executing ChooseLiftFloorCommand for floor: " + String(liftCommand.getFloor()));
}