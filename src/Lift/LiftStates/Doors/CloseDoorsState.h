#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class CloseDoorsState : public ElevatorState
{
private:
    LiftController* controller;
    unsigned long endTime = 0;
public:
    CloseDoorsState(LiftController* controller);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};