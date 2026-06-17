#pragma once

#include <map>
#include "Commands/ILiftCommandHandler.h"
#include "Commands/RequestLiftHandler.h"
#include "Commands/ChooseLiftFloorCommandHandler.h"
#include "Commands/StatusCommandHandler.h"
#include "Commands/ResetLiftCommandHandler.h"
#include "Commands/CommandFactory.h"

class LiftController;
class WebSocketHandler;
class LiftCommandScheduler;

class CommandRegistry
{
private:
    static RequestLiftHandler* requestLiftHandler;
    static ChooseLiftFloorCommandHandler* chooseLiftFloorHandler;
    static StatusCommandHandler* statusHandler;
    static ResetLiftCommandHandler* resetLiftHandler;
    static std::map<String, ILiftCommandHandler*> handlerMap;
public:
    static void init(LiftController* controller, WebSocketHandler* wsHandler, LiftCommandScheduler* scheduler);
    static ILiftCommandHandler* convertHandler(const String& commandName);
};