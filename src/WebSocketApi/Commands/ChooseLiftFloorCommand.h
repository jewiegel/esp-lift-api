#pragma once

#include "ICommand.h"

class ChooseLiftFloorCommand : public ICommand
{
private:
    int floor;
public:
    ChooseLiftFloorCommand(int floor) : floor(floor) {}
    ~ChooseLiftFloorCommand() {}

    String getName() const override {
        return "ChooseLiftFloor";
    }

    int getFloor() const {
        return floor;
    }
};