#pragma once

#include "ISwitchDriver.h"
#include <Arduino.h>

class SwitchDriver : public ISwitchDriver
{
private:
    int pin;
    std::function<void()> callback;
    bool lastState;
public:
    SwitchDriver(int pin);
    void onTrigger(std::function<void()> callback) override;
    bool isTriggered() override;
    void update() override;
};
