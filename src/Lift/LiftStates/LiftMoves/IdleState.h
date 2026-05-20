#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class IdleState : public ElevatorState
{
private:
    LiftController* controller;
public:
    IdleState(LiftController* controller);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};
