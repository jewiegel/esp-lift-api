#pragma once

#include "ICommand.h"

class StatusCommand : public ICommand
{
public:
    StatusCommand() {}
    ~StatusCommand() {}

    String getName() const override
    {
        return "Status";
    }
};
