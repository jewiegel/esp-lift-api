#pragma once

#include "ICommand.h"

class RequestLiftCommand : public ICommand
{
private:
    int currentFloor;
public:
    RequestLiftCommand(int floor) : currentFloor(floor) {}
    ~RequestLiftCommand() {}

    String getName() const override 
    {
        return "RequestLift";
    }

    int getCurrentFloor() const 
    {
        return currentFloor;
    }
};