#include "RequestLiftHandler.h"

RequestLiftHandler::RequestLiftHandler()
{
}

RequestLiftHandler::~RequestLiftHandler()
{
}

void RequestLiftHandler::execute(const ICommand &command)
{
    const RequestLiftCommand &liftCommand = static_cast<const RequestLiftCommand&>(command);

    Serial.println("Executing RequestLiftCommand for floor: " + String(liftCommand.getCurrentFloor()));
}
