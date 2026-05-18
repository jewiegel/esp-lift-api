#include "LedDriver.h"

LedDriver::LedDriver(int pin) : pin(pin)
{
    pinMode(pin, OUTPUT);
}

void LedDriver::on()
{
    digitalWrite(pin, HIGH);
}

void LedDriver::off()
{
    digitalWrite(pin, LOW);
}
