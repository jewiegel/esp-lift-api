#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class OpenDoorsState : public ElevatorState
{
private:
    LiftController* controller;
    unsigned long endTime = 0;
    bool doorsFullyOpen = false;
    bool autoClose;
public:
    OpenDoorsState(LiftController* controller, bool autoClose = true);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};