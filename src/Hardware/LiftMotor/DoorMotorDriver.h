#pragma once

#include "IBinaryMotorDriver.h"
#include <Arduino.h>

class DoorMotor : public IBinaryMotorDriver
{
private:
    int pinUp;
    int pinDown;
public:
    DoorMotor(int pinUp, int pinDown);
    ~DoorMotor();
    void goUp() override;
    void goDown() override;
    void stop() override;

};
