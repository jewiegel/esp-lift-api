#include "LiftController.h"
#include "LiftStates/Doors/OpenDoorsState.h"
#include "LiftStates/Doors/CloseDoorsState.h"
#include "LiftStates/LiftMoves/IdleState.h"
#include "LiftStates/LiftMoves/MovingState.h"
#include "../WebSocketApi/LiftCommandScheduler.h"
#include "../WebSocketApi/Commands/ChooseLiftFloorCommand.h"
#include "../WebSocketApi/Commands/RequestLiftCommand.h"
#include "../WebSocketApi/Commands/ResetLiftCommand.h"

LiftController::LiftController(LiftCommandScheduler* scheduler) : scheduler(scheduler)
{
}

LiftController::~LiftController()
{
    delete currentState;
    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        delete floorButtons[i];
    }
    delete callButton;
    delete resetButton;
    delete motor;
    delete doorMotor;
}

void LiftController::setup()
{
    // Initialize floor buttons
    floorButtons[0] = new ButtonDriver(PIN_FLOOR_BTN_0);
    floorButtons[1] = new ButtonDriver(PIN_FLOOR_BTN_1);
    floorButtons[2] = new ButtonDriver(PIN_FLOOR_BTN_2);

    // Initialize reset button
    resetButton = new ButtonDriver(PIN_RESET_BTN);
    resetButton->onPress([this]() { scheduler->enqueue(new ResetLiftCommand()); });

    // Initialize floor switches
    floorSwitches[0] = new SwitchDriver(PIN_FLOOR_SWITCH_0);
    floorSwitches[1] = new SwitchDriver(PIN_FLOOR_SWITCH_1);
    floorSwitches[2] = new SwitchDriver(PIN_FLOOR_SWITCH_2);

    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        floorButtons[i]->onPress([this, i]() { scheduler->enqueue(new ChooseLiftFloorCommand(i, false)); });
    }

    // Initialize call button
    callButton = new ButtonDriver(PIN_CALL_BTN);
    callButton->onPress([this]() { scheduler->enqueue(new RequestLiftCommand(currentFloor, false)); });

    // Initialize lift motor
    motor = new LiftMotorDriver(MOVING_LIFT_UP, MOVING_LIFT_DOWN);

    // Initialize door motor
    doorMotor = new DoorMotor(MOVING_DOOR_UP, MOVING_DOOR_DOWN);

    // Enter initial idle state
    setState(new IdleState(this));
}

void LiftController::update()
{
    for (int i = 0; i < FLOOR_COUNT; i++) floorButtons[i]->update();
    for (int i = 0; i < FLOOR_COUNT; i++) floorSwitches[i]->update();
    callButton->update();
    resetButton->update();

    if (currentState) 
    {
        ElevatorState* next = currentState->update();
        if (next) setState(next);
    }
}

void LiftController::goToFloor(int floor)
{
    if (floor < 0 || floor >= FLOOR_COUNT) return;
    if (isMoving || doorsInMotion) return;

    pendingFloor = floor;

    if (doorsOpen) 
    {
        setState(new CloseDoorsState(this));
    } 
    else 
    {
        setState(new OpenDoorsState(this));
    }
}

void LiftController::moveToFloor(int floor)
{
    if (floor < 0 || floor >= FLOOR_COUNT) return;
    if (isMoving || doorsInMotion) return;

    if (floor == currentFloor)
    {
        if (!doorsOpen) setState(new OpenDoorsState(this, false));
        return;
    }

    pendingFloor = floor;

    if (doorsOpen)
        setState(new CloseDoorsState(this));
    else
        setState(new MovingState(this, floor));
}

void LiftController::resetLift()
{
    if (isMoving || doorsInMotion) return;

    pendingFloor = 0;

    if (doorsOpen)
    {
        // Close the doors first; CloseDoorsState then moves to floor 0 without reopening
        setState(new CloseDoorsState(this, false));
    }
    else if (currentFloor != 0)
    {
        // Doors already closed: move straight to floor 0 and keep them closed on arrival
        setState(new MovingState(this, 0, false));
    }
    else
    {
        // Already home with doors closed
        setState(new IdleState(this));
    }
}

void LiftController::openDoors()
{
    setState(new OpenDoorsState(this));
}

void LiftController::closeDoors()
{
    setState(new CloseDoorsState(this));
}

void LiftController::setState(ElevatorState* newState)
{
    if (currentState) 
    {
        currentState->onExit();
        delete currentState;
    }
    currentState = newState;
    if (currentState) currentState->onEnter();
}

void LiftController::setDoorStatus(DoorStatus status)
{
    doorsOpen = (status == DoorStatus::Open);
}

void LiftController::setCurrentFloor(int floor)
{
    if (floor >= 0 && floor < FLOOR_COUNT)
    {
        currentFloor = floor;
    }
}

void LiftController::motorUp()
{
    motor->goUp();
}

void LiftController::motorDown()
{
    motor->goDown();
}

void LiftController::stopMotor()
{
    motor->stop();
}

void LiftController::openDoor()
{
    doorMotor->goUp();
}

void LiftController::closeDoor()
{
    doorMotor->goDown();
}

void LiftController::stopDoor()
{
    doorMotor->stop();
}

void LiftController::registerRobotWait(int floor)
{
    if (floor >= 0 && floor < FLOOR_COUNT)
    {
        robotWaitFloors[floor] = true;
    }
}

void LiftController::robotReady()
{
    // Clear the wait for the floor the lift is currently at
    if (currentFloor >= 0 && currentFloor < FLOOR_COUNT)
    {
        robotWaitFloors[currentFloor] = false;
    }
}

bool LiftController::isWaitingForRobotHere() const
{
    // Holding only makes sense once the lift has arrived with its doors open
    return doorsOpen && robotWaitFloors[currentFloor];
}
