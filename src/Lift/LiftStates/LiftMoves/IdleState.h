#pragma once

#include "../IElevatorState.h"

class IdleState : public ElevatorState
{
    public:
        void onEnter() override;
        void onExit() override;
};
