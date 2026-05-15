#include "CommandRegistry.h"

RequestLiftHandler CommandRegistry::requestLiftHandler;
ChooseLiftFloorCommandHandler CommandRegistry::chooseLiftFloorHandler;

std::map<String, ILiftCommandHandler*> CommandRegistry::handlerMap = {
    {"RequestLift",    &requestLiftHandler},
    {"ChooseLiftFloor", &chooseLiftFloorHandler}
};

ILiftCommandHandler* CommandRegistry::convertHandler(const String &commandName)
{
    auto it = handlerMap.find(commandName);
    return it != handlerMap.end() ? it->second : nullptr;
}
