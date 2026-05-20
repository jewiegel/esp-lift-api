#include "SwitchDriver.h"

SwitchDriver::SwitchDriver(int pin) : pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
    lastRawState = digitalRead(pin);
    confirmedState = lastRawState;
}

void SwitchDriver::onTrigger(std::function<void()> callback)
{
    this->callback = callback;
}

bool SwitchDriver::isTriggered()
{
    return confirmedState == LOW;
}

void SwitchDriver::update()
{
    bool reading = digitalRead(pin);

    if (reading != lastRawState)
        lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) > debounceDelay && reading != confirmedState) {
        confirmedState = reading;
        if (confirmedState == LOW && callback)
            callback();
    }

    lastRawState = reading;
}
