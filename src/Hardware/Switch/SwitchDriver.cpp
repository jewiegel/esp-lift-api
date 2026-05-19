#include "SwitchDriver.h"

SwitchDriver::SwitchDriver(int pin) : pin(pin)
{
    pinMode(pin, INPUT);
    lastState = digitalRead(pin);
}

void SwitchDriver::onTrigger(std::function<void()> callback)
{
    this->callback = callback;
}

// IR sensor: LOW = beam broken / object detected
bool SwitchDriver::isTriggered()
{
    return digitalRead(pin) == LOW;
}

void SwitchDriver::update()
{
    bool currentState = isTriggered();

    if (currentState && !lastState && callback)
        callback();

    lastState = currentState;
}
