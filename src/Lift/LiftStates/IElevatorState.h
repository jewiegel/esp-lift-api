#pragma once

class ElevatorState
{
    public:
        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual ElevatorState* update() { return nullptr; }
};
