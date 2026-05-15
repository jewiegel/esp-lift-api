#pragma once

#include "ICommand.h"
#include <functional>

class ILiftCommandHandler
{
public:
    virtual void execute(const ICommand &command, std::function<void()> onCompleted) = 0;
    virtual void update() {}
};
