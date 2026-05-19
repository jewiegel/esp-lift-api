#pragma once

class ILedDriver
{
public:
    virtual ~ILedDriver() = default;

    virtual void on() = 0;
    virtual void off() = 0;
};
