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
    controller->openDoor();
    endTime = 0;
    startTime = millis();
}

void OpenDoorsState::onExit()
{
    controller->stopDoor();
    Serial.println("Exiting Open Doors state");
}

ElevatorState* OpenDoorsState::update()
{
    if (!doorsFullyOpen)
    {
        // Wait until the door physically reaches the open end-stop switch.
        // Failsafe: if the switch never triggers (broken switch / jammed door),
        // give up after OPEN_TIMEOUT_MS and proceed as if the doors are open
        // so the motor doesn't keep driving indefinitely.
        if (controller->isDoorFullyOpen() || millis() - startTime >= OPEN_TIMEOUT_MS)
        {
            if (!controller->isDoorFullyOpen())
                Serial.println("[State] Open-door switch not reached within 7s - failsafe timeout");
            doorsFullyOpen = true;
            controller->stopDoor();
            controller->setDoorsInMotion(false);
            Serial.println("[State] Doors open");
            controller->setDoorStatus(DoorStatus::Open);
            if (autoClose) endTime = millis() + 3000;
        }
        return nullptr;
    }

    // Fully open: auto-close after the stay-open delay (if enabled)
    if (autoClose && endTime != 0 && millis() >= endTime)
    {
        return new CloseDoorsState(controller);
    }
    return nullptr;
}
