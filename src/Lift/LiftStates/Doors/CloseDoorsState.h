#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class CloseDoorsState : public ElevatorState
{
private:
    LiftController* controller;
public:
    CloseDoorsState(LiftController* controller);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};