#pragma once

class ILiftMotorDriver
{
public:
    ~ILiftMotorDriver() = default;
    virtual void goUp() = 0;
    virtual void goDown() = 0;
    virtual void stop() = 0;
};
