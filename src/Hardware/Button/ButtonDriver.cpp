#include "ButtonDriver.h"

ButtonDriver::ButtonDriver(int pin) : pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
    lastState = digitalRead(pin);
}

void ButtonDriver::onPress(std::function<void()> callback)
{
    this->callback = callback;
}

void ButtonDriver::update()
{
    bool currentState = digitalRead(pin);

    if (currentState != lastState)
        lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // LOW because INPUT_PULLUP: pin reads LOW when button is pressed
        if (currentState == LOW && lastState == HIGH && callback)
            callback();
    }

    lastState = currentState;
}
