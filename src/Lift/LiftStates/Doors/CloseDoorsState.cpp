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
    startTime = millis();
}

void CloseDoorsState::onExit()
{
    controller->stopDoor();
    controller->setDoorsInMotion(false);
    Serial.println("Exiting Close Doors state");
}

ElevatorState* CloseDoorsState::update()
{
    // Wait until the door physically reaches the closed end-stop switch.
    // Failsafe: if the switch never triggers (broken switch / jammed door),
    // give up after CLOSE_TIMEOUT_MS and proceed as if the doors are closed
    // so the motor doesn't keep driving indefinitely.
    if (!controller->isDoorFullyClosed())
    {
        if (millis() - startTime < CLOSE_TIMEOUT_MS)
            return nullptr;
        Serial.println("[State] Close-door switch not reached within 7s - failsafe timeout");
    }

    int floor = controller->getPendingFloor();
    if (floor != -1 && floor != controller->getCurrentFloor())
    {
        controller->setPendingFloor(-1);
        return new MovingState(controller, floor, openDoorsOnArrival);
    }
    controller->setPendingFloor(-1);
    return new IdleState(controller);
}
