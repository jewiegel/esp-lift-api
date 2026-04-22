#include "CommandFactory.h"

std::map<String, ICommand* (*)(const JsonDocument &)> CommandFactory::commandMap = {
    {"RequestLiftCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        return new RequestLiftCommand(floor);
    }},
    {"ChooseLiftFloorCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        return new ChooseLiftFloorCommand(floor);
    }}
};

ICommand* CommandFactory::createCommand(const JsonDocument &doc)
{
    String commandName = doc["command"];
    if (commandMap.find(commandName) != commandMap.end()) {
        return commandMap[commandName](doc);
    }
    return nullptr;
}



