#pragma once

#include "ILiftCommandHandler.h"
#include "StatusCommand.h"
#include "Lift/LiftController.h"

class WebSocketHandler;
class LiftCommandScheduler;

class StatusCommandHandler : public ILiftCommandHandler
{
private:
    LiftController* controller;
    WebSocketHandler* wsHandler;
    LiftCommandScheduler* scheduler;
public:
    StatusCommandHandler(LiftController* controller, WebSocketHandler* wsHandler, LiftCommandScheduler* scheduler);
    ~StatusCommandHandler();

    void execute(const ICommand& command, std::function<void()> onCompleted) override;
};
