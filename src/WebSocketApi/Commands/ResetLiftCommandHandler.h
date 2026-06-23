#pragma once

#include "ILiftCommandHandler.h"
#include "ResetLiftCommand.h"
#include "Lift/LiftController.h"

class WebSocketHandler;

class ResetLiftCommandHandler : public ILiftCommandHandler
{
private:
    LiftController* controller;
    WebSocketHandler* wsHandler;
    std::function<void()> onCompleted;
public:
    ResetLiftCommandHandler(LiftController* controller, WebSocketHandler* wsHandler);
    ~ResetLiftCommandHandler();

    void execute(const ICommand& command, std::function<void()> onCompleted) override;
    void update() override;
};
