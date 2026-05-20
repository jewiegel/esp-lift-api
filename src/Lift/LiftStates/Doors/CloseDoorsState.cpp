#include "CloseDoorsState.h"

CloseDoorsState::CloseDoorsState(LiftController* controller) : controller(controller)
{
}

void CloseDoorsState::onEnter()
{
    Serial.println("[State] Doors closing");
    controller->setDoorStatus(DoorStatus::Closed);
}

void CloseDoorsState::onExit()
{
    Serial.println("Exiting Close Doors state");
}

ElevatorState* CloseDoorsState::update()
{
    return nullptr;
}
