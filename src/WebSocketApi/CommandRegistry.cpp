#include "CommandRegistry.h"

std::map<String, ILiftCommandHandler*> CommandRegistry::handlerConverter = {
    {"api/v1/lift/RequestLiftCommand", new RequestLiftHandler()},
    {"api/v1/lift/ChooseLiftFloorCommand", new ChooseLiftFloorCommandHandler()}
};

ILiftCommandHandler* CommandRegistry::convertHandler(const String &commandName)
{
    if (handlerConverter.find(commandName) != handlerConverter.end()) {
        return handlerConverter[commandName];
    }
    return nullptr;
}
