#pragma once

#include <Arduino.h>

class ICommand
{
public:
    virtual ~ICommand() {}
    virtual String getName() const = 0;

    // Target floor for movement commands, or -1 for commands without a floor.
    // Used by the scheduler to drop duplicate floor requests.
    virtual int getTargetFloor() const { return -1; }
};
