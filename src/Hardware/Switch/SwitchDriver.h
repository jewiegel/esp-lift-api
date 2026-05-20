#pragma once

#include "ISwitchDriver.h"
#include <Arduino.h>

class SwitchDriver : public ISwitchDriver
{
private:
    int pin;
    std::function<void()> callback;
    bool lastRawState;
    bool confirmedState;
    unsigned long lastDebounceTime = 0;
    static constexpr unsigned long debounceDelay = 50;
public:
    SwitchDriver(int pin);
    void onTrigger(std::function<void()> callback) override;
    bool isTriggered() override;
    void update() override;
};
