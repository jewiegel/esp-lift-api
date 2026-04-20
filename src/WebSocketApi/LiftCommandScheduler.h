#pragma once

#include "Commands/ICommand.h"

class LiftCommandScheduler
{
private:
    /* data */
public:
    LiftCommandScheduler(/* args */);
    ~LiftCommandScheduler();
    void enqueue(const ICommand &command);
};
