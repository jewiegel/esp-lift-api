#pragma once

#include "ILiftCommandHandler.h"
#include "RequestLiftCommand.h"
#include "Lift/LiftController.h"

class RequestLiftHandler : public ILiftCommandHandler
{
private:
    LiftController *controller;
    std::function<void()> onCompleted;
    unsigned long endTime = 0;
public:
    RequestLiftHandler(LiftController *controller);
    ~RequestLiftHandler();

    void execute(const ICommand &command, std::function<void()> onCompleted) override;
    void update() override;
};
