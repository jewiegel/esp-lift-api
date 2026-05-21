#include "CommandRegistry.h"
#include "WebSocketHandler.h"

RequestLiftHandler* CommandRegistry::requestLiftHandler = nullptr;
ChooseLiftFloorCommandHandler* CommandRegistry::chooseLiftFloorHandler = nullptr;
std::map<String, ILiftCommandHandler*> CommandRegistry::handlerMap;

void CommandRegistry::init(LiftController* controller, WebSocketHandler* wsHandler)
{
    requestLiftHandler = new RequestLiftHandler(controller, wsHandler);
    chooseLiftFloorHandler = new ChooseLiftFloorCommandHandler(controller, wsHandler);

    handlerMap["RequestLift"]     = requestLiftHandler;
    handlerMap["ChooseLiftFloor"] = chooseLiftFloorHandler;
}

ILiftCommandHandler* CommandRegistry::convertHandler(const String& commandName)
{
    auto it = handlerMap.find(commandName);
    return it != handlerMap.end() ? it->second : nullptr;
}
