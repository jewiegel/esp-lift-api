#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class CloseDoorsState : public ElevatorState
{
private:
    LiftController* controller;
    unsigned long endTime = 0;
    bool openDoorsOnArrival;
public:
    CloseDoorsState(LiftController* controller, bool openDoorsOnArrival = true);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};