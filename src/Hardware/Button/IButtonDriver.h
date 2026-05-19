#pragma once

#include <functional>

class IButtonDriver
{
public:
    virtual ~IButtonDriver() = default;

    virtual void onPress(std::function<void()> callback) = 0;
    virtual void update() = 0;
};
