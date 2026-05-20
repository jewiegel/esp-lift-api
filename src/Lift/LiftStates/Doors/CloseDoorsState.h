#pragma once

#include "../IElevatorState.h"

class CloseDoorsState : public ElevatorState
{
    public:
        void onEnter() override;
        void onExit() override;
};