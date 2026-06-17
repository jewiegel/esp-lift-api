#pragma once

#include "ILiftCommandHandler.h"
#include "RequestLiftCommand.h"
#include "Lift/LiftController.h"

class WebSocketHandler;

class RequestLiftHandler : public ILiftCommandHandler
{
private:
    LiftController* controller;
    WebSocketHandler* wsHandler;
    std::function<void()> onCompleted;
    int targetFloor = -1;
    bool arrivedAnnounced = false;
public:
    RequestLiftHandler(LiftController* controller, WebSocketHandler* wsHandler);
    ~RequestLiftHandler();

    void execute(const ICommand& command, std::function<void()> onCompleted) override;
    void update() override;
};
