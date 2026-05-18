#pragma once

#include <functional>

class ISwitchDriver
{
public:
    virtual ~ISwitchDriver() = default;

    virtual void onTrigger(std::function<void()> callback) = 0;
    virtual bool isTriggered() = 0;
    virtual void update() = 0;
};
