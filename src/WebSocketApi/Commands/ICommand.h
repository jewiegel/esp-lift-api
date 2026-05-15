#pragma once

#include <Arduino.h>

class ICommand
{
public:
    virtual ~ICommand() {}
    virtual String getName() const = 0;
};
