#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class MovingState : public ElevatorState
{
private:
    LiftController* controller;
    int targetFloor;
    int currentStepFloor;
    int nextFloor;
    bool lastSwitchState = false;
public:
    MovingState(LiftController* controller, int targetFloor);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};