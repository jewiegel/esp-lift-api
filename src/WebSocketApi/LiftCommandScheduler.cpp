#include "LiftCommandScheduler.h"

LiftCommandScheduler::LiftCommandScheduler()
{
}

LiftCommandScheduler::~LiftCommandScheduler()
{
}

void LiftCommandScheduler::enqueue(ICommand* command)
{
    commandQueue.push(command);
}