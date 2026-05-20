#pragma once

#include "../IElevatorState.h"

class MovingState : public ElevatorState
{
    public:
        void onEnter() override;
        void onExit() override;
};