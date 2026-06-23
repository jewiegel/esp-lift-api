#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class CloseDoorsState : public ElevatorState
{
private:
    LiftController* controller;
    bool openDoorsOnArrival;
    unsigned long startTime = 0;
    static constexpr unsigned long CLOSE_TIMEOUT_MS = 7000;
public:
    CloseDoorsState(LiftController* controller, bool openDoorsOnArrival = true);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};