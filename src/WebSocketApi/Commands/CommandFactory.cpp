#include "CommandFactory.h"

std::map<String, ICommand* (*)(const JsonDocument &)> CommandFactory::commandMap = 
{
    {String(apiVersion) + "RequestLiftCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        bool waitForRobot = doc["waitForRobot"] | false;
        return new RequestLiftCommand(floor, waitForRobot);
    }},
    {String(apiVersion) + "ChooseLiftFloorCommand", [](const JsonDocument &doc) -> ICommand* {
        int floor = doc["floor"];
        bool waitForRobot = doc["waitForRobot"] | false;
        return new ChooseLiftFloorCommand(floor, waitForRobot);
    }},
    {String(apiVersion) + "StatusCommand", [](const JsonDocument &doc) -> ICommand* {
        return new StatusCommand();
    }},
    {String(apiVersion) + "ResetLiftCommand", [](const JsonDocument &doc) -> ICommand* {
        return new ResetLiftCommand();
    }},
    {String(apiVersion) + "RobotReadyCommand", [](const JsonDocument &doc) -> ICommand* {
        return new RobotReadyCommand();
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



