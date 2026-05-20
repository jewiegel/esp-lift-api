#include "IdleState.h"

IdleState::IdleState(LiftController* controller) : controller(controller)
{
}

void IdleState::onEnter()
{
    Serial.println("[State] Idle — doors closed");
    controller->setDoorStatus(DoorStatus::Closed);
}

void IdleState::onExit()
{
    Serial.println("Exiting Idle state");
}

ElevatorState* IdleState::update()
{
    return nullptr;
}
