#pragma once

#include "ILiftCommandHandler.h"
#include "ChooseLiftFloorCommand.h"
#include "Lift/LiftController.h"

class ChooseLiftFloorCommandHandler : public ILiftCommandHandler
{
private:
    std::function<void()> onCompleted;
    unsigned long endTime = 0;
    LiftController *controller;
public:
    ChooseLiftFloorCommandHandler(LiftController *controller);
    ~ChooseLiftFloorCommandHandler();

    void execute(const ICommand &command, std::function<void()> onCompleted) override;
    void update() override;
};