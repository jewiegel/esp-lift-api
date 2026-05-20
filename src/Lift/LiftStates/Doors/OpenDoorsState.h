#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class OpenDoorsState : public ElevatorState
{
private:
    LiftController* controller;
public:
    OpenDoorsState(LiftController* controller);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};