#pragma once

#include "ICommand.h"

class ResetLiftCommand : public ICommand
{
public:
    ResetLiftCommand();
    ~ResetLiftCommand();

    String getName() const override;
};
