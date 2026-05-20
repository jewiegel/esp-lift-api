#include "MovingState.h"
#include "../../LiftStates/Doors/OpenDoorsState.h"

MovingState::MovingState(LiftController* controller, int targetFloor) : controller(controller), targetFloor(targetFloor), currentStepFloor(0)
{
}

void MovingState::onEnter()
{
    currentStepFloor = controller->getCurrentFloor();
    int direction = (targetFloor > currentStepFloor) ? 1 : -1;
    nextFloor = currentStepFloor + direction;
    lastSwitchState = false;
    controller->setIsMoving(true);
    Serial.println("[State] Moving to floor: " + String(targetFloor));
    controller->setDoorStatus(DoorStatus::Closed);
}

void MovingState::onExit()
{
    controller->setIsMoving(false);
    Serial.println("Exiting Moving state");
}

ElevatorState* MovingState::update()
{
    bool triggered = controller->getFloorSwitch(nextFloor)->isTriggered();

    if (triggered && !lastSwitchState) {
        currentStepFloor = nextFloor;
        controller->turnOnFloorLed(currentStepFloor);
        Serial.println("[State] Arrived at floor: " + String(currentStepFloor));

        if (currentStepFloor == targetFloor) {
            return new OpenDoorsState(controller);
        }

        int direction = (targetFloor > currentStepFloor) ? 1 : -1;
        nextFloor = currentStepFloor + direction;
    }

    lastSwitchState = triggered;
    return nullptr;
}
