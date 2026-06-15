#include "ServoDriver.h"
#include <Arduino.h>

static const unsigned long DOOR_MOVE_MS = 5000;
static const int SPEED_OPEN  = 0;
static const int SPEED_CLOSE = 180;
static const int SPEED_STOP  = 90;

ServoDriver::ServoDriver() {}

void ServoDriver::attach(int pin)
{
    servo.attach(pin, 500, 2400);
}

void ServoDriver::write(int angle)
{
    servo.write(angle);
}

int ServoDriver::read()
{
    return servo.read();
}

void ServoDriver::open()
{
    servo.write(SPEED_OPEN);
    _moveStart = millis();
    _moving = true;
}

void ServoDriver::close()
{
    servo.write(SPEED_CLOSE);
    _moveStart = millis();
    _moving = true;
}

void ServoDriver::update()
{
    if (_moving && millis() - _moveStart >= DOOR_MOVE_MS)
    {
        servo.write(SPEED_STOP);
        _moving = false;
    }
}
