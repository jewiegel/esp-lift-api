#pragma once

#include "ICommand.h"

class RobotReadyCommand : public ICommand
{
public:
    RobotReadyCommand() {}
    ~RobotReadyCommand() {}

    String getName() const override
    {
        return "RobotReady";
    }
};
