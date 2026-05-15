#include "CommandFactory.h"

std::map<String, ICommand* (*)(const JsonDocument &)> CommandFactory::commandMap = {
    {String(apiVersion) + "RequestLiftCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        return new RequestLiftCommand(floor);
    }},
    {String(apiVersion) + "ChooseLiftFloorCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        return new ChooseLiftFloorCommand(floor);
    }}
};

ICommand* CommandFactory::createCommand(const JsonDocument &doc)
{
    String commandName = doc["command"].as<const char*>();
    if (commandMap.find(commandName) != commandMap.end()) {
        return commandMap[commandName](doc);
    }
    return nullptr;
}



