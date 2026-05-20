#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class MovingState : public ElevatorState
{
private:
    LiftController* controller;
    int targetFloor;
public:
    MovingState(LiftController* controller, int targetFloor);
    void onEnter() override;
    void onExit() override;
};