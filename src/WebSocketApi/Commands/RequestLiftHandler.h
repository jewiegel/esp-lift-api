#pragma once

#include "ILiftCommandHandler.h"
#include "RequestLiftCommand.h"

class RequestLiftHandler : public ILiftCommandHandler
{
private:
    std::function<void()> onCompleted;
    unsigned long endTime = 0;
public:
    RequestLiftHandler();
    ~RequestLiftHandler();

    void execute(const ICommand &command, std::function<void()> onCompleted) override;
    void update() override;
};
