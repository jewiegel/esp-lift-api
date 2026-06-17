#pragma once

class IBinaryMotorDriver
{
public:
    virtual ~IBinaryMotorDriver() = default;
    virtual void goUp() = 0;
    virtual void goDown() = 0;
    virtual void stop() = 0;
};
