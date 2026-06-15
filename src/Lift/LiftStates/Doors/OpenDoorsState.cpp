#include "OpenDoorsState.h"
#include "CloseDoorsState.h"

OpenDoorsState::OpenDoorsState(LiftController* controller, bool autoClose) : controller(controller), autoClose(autoClose)
{
}

void OpenDoorsState::onEnter()
{
    doorsFullyOpen = false;
    controller->setDoorsInMotion(true);
    Serial.println("[State] Doors opening");
    controller->setDoorStatus(DoorStatus::Moving);
    endTime = millis() + 3000;
}

void OpenDoorsState::onExit()
{
    Serial.println("Exiting Open Doors state");
}

ElevatorState* OpenDoorsState::update()
{
    if (endTime != 0 && millis() >= endTime) 
    {
        endTime = 0;
        if (!doorsFullyOpen)
        {
            doorsFullyOpen = true;
            controller->setDoorsInMotion(false);
            Serial.println("[State] Doors open");
            controller->setDoorStatus(DoorStatus::Open);
            if (autoClose) endTime = millis() + 3000;
        }
        else
        {
            return new CloseDoorsState(controller);
        }
    }
    return nullptr;
}
