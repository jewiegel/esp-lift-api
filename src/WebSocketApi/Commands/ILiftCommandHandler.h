#pragma once

#include "ICommand.h"

class ILiftCommandHandler
{
public:
    virtual void execute(const ICommand &command) = 0;
};
