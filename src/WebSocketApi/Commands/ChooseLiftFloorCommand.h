#pragma once

#include "ICommand.h"

class ChooseLiftFloorCommand : public ICommand
{
private:
    int floor;
    bool waitForRobot;
public:
    ChooseLiftFloorCommand(int floor, bool waitForRobot) : floor(floor), waitForRobot(waitForRobot) {}
    ~ChooseLiftFloorCommand() {}

    String getName() const override
    {
        return "ChooseLiftFloor";
    }

    int getFloor() const
    {
        return floor;
    }

    bool getWaitForRobot() const
    {
        return waitForRobot;
    }
};