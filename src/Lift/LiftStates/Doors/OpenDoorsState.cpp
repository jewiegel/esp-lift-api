#include "OpenDoorsState.h"

OpenDoorsState::OpenDoorsState(LiftController* controller) : controller(controller)
{
}

void OpenDoorsState::onEnter()
{
    Serial.println("[State] Doors open");
    controller->setDoorStatus(DoorStatus::Open);
}

void OpenDoorsState::onExit()
{
    Serial.println("Exiting Open Doors state");
}
