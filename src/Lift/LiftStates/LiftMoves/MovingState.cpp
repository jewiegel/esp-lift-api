#include "MovingState.h"

MovingState::MovingState(LiftController* controller, int targetFloor) : controller(controller), targetFloor(targetFloor)
{
}

void MovingState::onEnter()
{
    Serial.println("[State] Moving to floor: " + String(targetFloor));
    controller->setDoorStatus(DoorStatus::Moving);
}

void MovingState::onExit()
{
    Serial.println("Exiting Moving state");
}
