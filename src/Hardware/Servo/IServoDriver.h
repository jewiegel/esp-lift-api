#pragma once

class IServoDriver
{
public:
    virtual ~IServoDriver() = default;

    virtual void attach(int pin) = 0;
    virtual void write(int angle) = 0;
    virtual int read() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void update() = 0;
};