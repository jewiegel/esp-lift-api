#pragma once

#include "ILiftCommandHandler.h"
#include "ChooseLiftFloorCommand.h"

class ChooseLiftFloorCommandHandler : public ILiftCommandHandler
{
private:
    std::function<void()> onCompleted;
    unsigned long endTime = 0;
public:
    ChooseLiftFloorCommandHandler();
    ~ChooseLiftFloorCommandHandler();

    void execute(const ICommand &command, std::function<void()> onCompleted) override;
    void update() override;
};