#include "DoorMotorDriver.h"

DoorMotor::DoorMotor(int pinUp, int pinDown) : pinUp(pinUp), pinDown(pinDown)
{
    pinMode(pinUp, OUTPUT);
    pinMode(pinDown, OUTPUT);
    stop();
}

DoorMotor::~DoorMotor()
{
}

void DoorMotor::goUp()
{
    digitalWrite(pinDown, HIGH);
    digitalWrite(pinUp, LOW);
}

void DoorMotor::goDown()
{
    digitalWrite(pinUp, HIGH);
    digitalWrite(pinDown, LOW);
}

void DoorMotor::stop()
{
    digitalWrite(pinUp, HIGH);
    digitalWrite(pinDown, HIGH);
}
