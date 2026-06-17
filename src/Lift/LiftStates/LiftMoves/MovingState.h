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
    bool openDoorsOnArrival;
public:
    MovingState(LiftController* controller, int targetFloor, bool openDoorsOnArrival = true);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};