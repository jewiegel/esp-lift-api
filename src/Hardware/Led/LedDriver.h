#pragma once

#include "ILedDriver.h"
#include <Arduino.h>

class LedDriver : public ILedDriver
{
private:
    int pin;
public:
    LedDriver(int pin);
    void on() override;
    void off() override;
};
