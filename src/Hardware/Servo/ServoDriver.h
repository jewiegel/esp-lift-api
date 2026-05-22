#pragma once

#include <ESP32Servo.h>
#include "IServoDriver.h"

class ServoDriver : public IServoDriver
{
private:
    Servo servo;
    unsigned long _moveStart = 0;
    bool _moving = false;

public:
    ServoDriver();
    void attach(int pin) override;
    void write(int angle) override;
    int read() override;
    void open() override;
    void close() override;
    void update() override;
};