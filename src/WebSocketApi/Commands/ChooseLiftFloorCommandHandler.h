#pragma once

#include "ILiftCommandHandler.h"
#include "ChooseLiftFloorCommand.h"
#include "Lift/LiftController.h"

class WebSocketHandler;

class ChooseLiftFloorCommandHandler : public ILiftCommandHandler
{
private:
    LiftController* controller;
    WebSocketHandler* wsHandler;
    std::function<void()> onCompleted;
    int targetFloor = -1;
public:
    ChooseLiftFloorCommandHandler(LiftController* controller, WebSocketHandler* wsHandler);
    ~ChooseLiftFloorCommandHandler();

    void execute(const ICommand& command, std::function<void()> onCompleted) override;
    void update() override;
};