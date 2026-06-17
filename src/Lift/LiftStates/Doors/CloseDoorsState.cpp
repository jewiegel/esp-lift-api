#include "CloseDoorsState.h"
#include "../LiftMoves/IdleState.h"
#include "../LiftMoves/MovingState.h"

CloseDoorsState::CloseDoorsState(LiftController* controller, bool openDoorsOnArrival)
    : controller(controller), openDoorsOnArrival(openDoorsOnArrival)
{
}

void CloseDoorsState::onEnter()
{
    controller->setDoorsInMotion(true);
    Serial.println("[State] Doors closing");
    controller->setDoorStatus(DoorStatus::Moving);
    controller->closeDoor();
    endTime = millis() + 6000;
}

void CloseDoorsState::onExit()
{
    controller->stopDoor();
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
            return new MovingState(controller, floor, openDoorsOnArrival);
        }
        controller->setPendingFloor(-1);
        return new IdleState(controller);
    }
    return nullptr;
}
