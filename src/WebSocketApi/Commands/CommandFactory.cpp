#include "CommandFactory.h"

std::map<String, ICommand* (*)(const JsonDocument &)> CommandFactory::commandMap = 
{
    {String(apiVersion) + "RequestLiftCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        return new RequestLiftCommand(floor);
    }},
    {String(apiVersion) + "ChooseLiftFloorCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        return new ChooseLiftFloorCommand(floor);
    }},
    {String(apiVersion) + "StatusCommand", [](const JsonDocument &doc) -> ICommand* {
        return new StatusCommand();
    }},
    {String(apiVersion) + "ResetLiftCommand", [](const JsonDocument &doc) -> ICommand* {
        return new ResetLiftCommand();
    }}
};

ICommand* CommandFactory::createCommand(const JsonDocument &doc)
{
    String commandName = doc["command"].as<const char*>();
    if (commandMap.find(commandName) != commandMap.end()) 
    {
        return commandMap[commandName](doc);
    }
    return nullptr;
}



