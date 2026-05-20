#include "MovingState.h"
#include "../../LiftStates/Doors/OpenDoorsState.h"

MovingState::MovingState(LiftController* controller, int targetFloor) : controller(controller), targetFloor(targetFloor), currentStepFloor(0)
{
}

void MovingState::onEnter()
{
    currentStepFloor = controller->getCurrentFloor();
    nextStepTime = millis() + 4000;
    Serial.println("[State] Moving to floor: " + String(targetFloor));
    controller->setDoorStatus(DoorStatus::Moving);
}

void MovingState::onExit()
{
    Serial.println("Exiting Moving state");
}

ElevatorState* MovingState::update()
{
    if (millis() < nextStepTime) return nullptr;

    int step = (targetFloor > currentStepFloor) ? 1 : -1;
    currentStepFloor += step;
    controller->turnOnFloorLed(currentStepFloor);

    Serial.println("[State] Passing floor: " + String(currentStepFloor));

    if (currentStepFloor == targetFloor) {
        return new OpenDoorsState(controller);
    }

    nextStepTime = millis() + 4000;
    return nullptr;
}
