#include "ChooseLiftFloorCommandHandler.h"

ChooseLiftFloorCommandHandler::ChooseLiftFloorCommandHandler()
{
}

ChooseLiftFloorCommandHandler::~ChooseLiftFloorCommandHandler()
{
}

void ChooseLiftFloorCommandHandler::execute(const ICommand &command)
{
    const ChooseLiftFloorCommand &floorCommand = static_cast<const ChooseLiftFloorCommand&>(command);
    Serial.println("Executing ChooseLiftFloorCommand for floor: " + String(floorCommand.getFloor()));
}