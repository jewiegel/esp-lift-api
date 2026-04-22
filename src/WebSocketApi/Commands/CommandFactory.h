#pragma once

#include "ICommand.h"
#include "RequestLiftCommand.h"
#include "ChooseLiftFloorCommand.h"

#include <map>
#include <ArduinoJson.h>

class CommandFactory
{
private:
    static std::map<String, ICommand* (*)(const JsonDocument &)> commandMap;
public:

public:
    static ICommand* createCommand(const JsonDocument &doc);
};