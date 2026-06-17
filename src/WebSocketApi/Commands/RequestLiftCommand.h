#pragma once

#include "ICommand.h"

class RequestLiftCommand : public ICommand
{
private:
    int currentFloor;
    bool waitForRobot;
public:
    RequestLiftCommand(int floor, bool waitForRobot) : currentFloor(floor), waitForRobot(waitForRobot) {}
    ~RequestLiftCommand() {}

    String getName() const override 
    {
        return "RequestLift";
    }

    int getCurrentFloor() const 
    {
        return currentFloor;
    }

    bool getWaitForRobot() const
    {
        return waitForRobot;
    }
};