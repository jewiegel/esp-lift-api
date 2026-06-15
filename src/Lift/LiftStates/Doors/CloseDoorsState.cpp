#include "CloseDoorsState.h"
#include "../LiftMoves/IdleState.h"
#include "../LiftMoves/MovingState.h"

CloseDoorsState::CloseDoorsState(LiftController* controller) : controller(controller)
{
}

void CloseDoorsState::onEnter()
{
    controller->setDoorsInMotion(true);
    Serial.println("[State] Doors closing");
    controller->setDoorStatus(DoorStatus::Moving);
    endTime = millis() + 3000;
}

void CloseDoorsState::onExit()
{
    controller->setDoorsInMotion(false);
    Serial.println("Exiting Close Doors state");
}

ElevatorState* CloseDoorsState::update()
{
    if (endTime != 0 && millis() >= endTime) 
    {
        endTime = 0;
        int floor = controller->getPendingFloor();
        if (floor != -1 && floor != controller->getCurrentFloor()) 
        {
            controller->setPendingFloor(-1);
            return new MovingState(controller, floor);
        }
        controller->setPendingFloor(-1);
        return new IdleState(controller);
    }
    return nullptr;
}
