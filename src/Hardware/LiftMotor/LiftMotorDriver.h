#pragma once

#include "ILiftMotorDriver.h"
#include <Arduino.h>

class LiftMotorDriver : public ILiftMotorDriver
{
private:
    int pinUp;
    int pinDown;
public:
    LiftMotorDriver(int pinUp, int pinDown);
    ~LiftMotorDriver();
    void goUp() override;
    void goDown() override;
    void stop() override;
};
