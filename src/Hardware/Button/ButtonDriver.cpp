#include "ButtonDriver.h"

ButtonDriver::ButtonDriver(int pin) : pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
    lastRawState = digitalRead(pin);
    confirmedState = lastRawState;
}

void ButtonDriver::onPress(std::function<void()> callback)
{
    this->callback = callback;
}

void ButtonDriver::update()
{
    bool reading = digitalRead(pin);

    if (reading != lastRawState)
        lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) > debounceDelay && reading != confirmedState) 
    {
        confirmedState = reading;
        if (confirmedState == LOW && callback)
            callback();
    }

    lastRawState = reading;
}
