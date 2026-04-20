#pragma once

#include <map>
#include "Commands/ILiftCommandHandler.h"
#include "Commands/ICommand.h"

class CommandRegistry
{
private:
    std::map<String, ILiftCommandHandler*> handlerConverter;
public:
    ILiftCommandHandler* convertHandler(const String &commandName) {
        if (handlerConverter.find(commandName) != handlerConverter.end()) {
            return handlerConverter[commandName];
        }
        return nullptr;
    }
};