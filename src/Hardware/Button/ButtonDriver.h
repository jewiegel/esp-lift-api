#pragma once

#include "IButtonDriver.h"
#include <Arduino.h>

class ButtonDriver : public IButtonDriver
{
private:
    int pin;
    std::function<void()> callback;
    bool lastState;
    unsigned long lastDebounceTime = 0;
    static constexpr unsigned long debounceDelay = 50;
public:
    ButtonDriver(int pin);
    void onPress(std::function<void()> callback) override;
    void update() override;
};
