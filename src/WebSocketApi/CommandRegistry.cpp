#include "CommandRegistry.h"
#include "WebSocketHandler.h"

RequestLiftHandler* CommandRegistry::requestLiftHandler = nullptr;
ChooseLiftFloorCommandHandler* CommandRegistry::chooseLiftFloorHandler = nullptr;
StatusCommandHandler* CommandRegistry::statusHandler = nullptr;
ResetLiftCommandHandler* CommandRegistry::resetLiftHandler = nullptr;
std::map<String, ILiftCommandHandler*> CommandRegistry::handlerMap;

void CommandRegistry::init(LiftController* controller, WebSocketHandler* wsHandler, LiftCommandScheduler* scheduler)
{
    requestLiftHandler = new RequestLiftHandler(controller, wsHandler);
    chooseLiftFloorHandler = new ChooseLiftFloorCommandHandler(controller, wsHandler);
    statusHandler = new StatusCommandHandler(controller, wsHandler, scheduler);
    resetLiftHandler = new ResetLiftCommandHandler(controller, wsHandler);

    handlerMap["RequestLift"]     = requestLiftHandler;
    handlerMap["ChooseLiftFloor"] = chooseLiftFloorHandler;
    handlerMap["Status"]          = statusHandler;
    handlerMap["ResetLift"]       = resetLiftHandler;
}

ILiftCommandHandler* CommandRegistry::convertHandler(const String& commandName)
{
    auto it = handlerMap.find(commandName);
    return it != handlerMap.end() ? it->second : nullptr;
}
