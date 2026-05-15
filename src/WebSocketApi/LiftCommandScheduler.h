#pragma once

#include "Commands/ICommand.h"
#include <queue>

class LiftCommandScheduler
{
private:
    std::queue<ICommand*> commandQueue;
public:
    LiftCommandScheduler();
    ~LiftCommandScheduler();
    void enqueue(ICommand* command);
};
