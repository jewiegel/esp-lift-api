#pragma once

#include "../IElevatorState.h"
#include "../../LiftController.h"

class OpenDoorsState : public ElevatorState
{
private:
    LiftController* controller;
    unsigned long endTime = 0;
    unsigned long startTime = 0;
    bool doorsFullyOpen = false;
    bool autoClose;
    static constexpr unsigned long OPEN_TIMEOUT_MS = 7000;
public:
    OpenDoorsState(LiftController* controller, bool autoClose = true);
    void onEnter() override;
    void onExit() override;
    ElevatorState* update() override;
};