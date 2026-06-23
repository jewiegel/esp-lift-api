#include "LiftMotorDriver.h"

LiftMotorDriver::LiftMotorDriver(int pinUp, int pinDown) : pinUp(pinUp), pinDown(pinDown)
{
    pinMode(pinUp, OUTPUT);
    pinMode(pinDown, OUTPUT);
    stop();
}

LiftMotorDriver::~LiftMotorDriver()
{
}

void LiftMotorDriver::goUp()
{
    digitalWrite(pinDown, LOW);
    digitalWrite(pinUp, HIGH);
}

void LiftMotorDriver::goDown()
{
    digitalWrite(pinUp, LOW);
    digitalWrite(pinDown, HIGH);
}

void LiftMotorDriver::stop()
{
    digitalWrite(pinUp, LOW);
    digitalWrite(pinDown, LOW);
}
