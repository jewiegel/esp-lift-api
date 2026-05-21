#pragma once

#include <map>
#include "Commands/ILiftCommandHandler.h"
#include "Commands/RequestLiftHandler.h"
#include "Commands/ChooseLiftFloorCommandHandler.h"
#include "Commands/CommandFactory.h"

class LiftController;
class WebSocketHandler;

class CommandRegistry
{
private:
    static RequestLiftHandler* requestLiftHandler;
    static ChooseLiftFloorCommandHandler* chooseLiftFloorHandler;
    static std::map<String, ILiftCommandHandler*> handlerMap;
public:
    static void init(LiftController* controller, WebSocketHandler* wsHandler);
    static ILiftCommandHandler* convertHandler(const String& commandName);
};