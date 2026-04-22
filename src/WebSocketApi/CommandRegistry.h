#pragma once

#include <map>
#include "Commands/ILiftCommandHandler.h"
#include "Commands/RequestLiftHandler.h"
#include "Commands/ChooseLiftFloorCommandHandler.h"
#include "Commands/ICommand.h"

class CommandRegistry
{
private:
    static std::map<String, ILiftCommandHandler*> handlerConverter;
public:
    static ILiftCommandHandler* convertHandler(const String &commandName);
};