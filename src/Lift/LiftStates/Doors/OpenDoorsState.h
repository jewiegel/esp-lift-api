#pragma once

#include "../IElevatorState.h"

class OpenDoorsState : public ElevatorState
{
    public:
        void onEnter() override;
        void onExit() override;
};