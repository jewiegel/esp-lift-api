#include "RequestLiftHandler.h"

RequestLiftHandler::RequestLiftHandler(LiftController *controller) : controller(controller)
{
}

RequestLiftHandler::~RequestLiftHandler()
{
}

void RequestLiftHandler::execute(const ICommand &command, std::function<void()> onCompleted)
{
    const RequestLiftCommand &liftCommand = static_cast<const RequestLiftCommand&>(command);
    this->onCompleted = onCompleted;
}

void RequestLiftHandler::update()
{
    onCompleted();
}
