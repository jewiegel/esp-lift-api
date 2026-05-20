#include "LiftController.h"
#include "LiftStates/Doors/OpenDoorsState.h"
#include "LiftStates/Doors/CloseDoorsState.h"
#include "LiftStates/LiftMoves/IdleState.h"
#include "LiftStates/LiftMoves/MovingState.h"

LiftController::LiftController()
{
}

LiftController::~LiftController()
{
    delete currentState;
    for (int i = 0; i < FLOOR_COUNT; i++) {
        delete floorLeds[i];
        delete floorButtons[i];
    }
    for (int i = 0; i < 3; i++) delete doorStatusLeds[i];
    delete callButton;
}

void LiftController::setup()
{
    // Initialize floor LEDs
    floorLeds[0] = new LedDriver(PIN_FLOOR_LED_0);
    floorLeds[1] = new LedDriver(PIN_FLOOR_LED_1);
    floorLeds[2] = new LedDriver(PIN_FLOOR_LED_2);
    floorLeds[3] = new LedDriver(PIN_FLOOR_LED_3);

    // Initialize door status LEDs
    doorStatusLeds[0] = new LedDriver(PIN_DOOR_LED_OPEN);
    doorStatusLeds[1] = new LedDriver(PIN_DOOR_LED_CLOSED);
    doorStatusLeds[2] = new LedDriver(PIN_DOOR_LED_MOVING);

    // Initialize floor buttons
    floorButtons[0] = new ButtonDriver(PIN_FLOOR_BTN_0);
    floorButtons[1] = new ButtonDriver(PIN_FLOOR_BTN_1);
    floorButtons[2] = new ButtonDriver(PIN_FLOOR_BTN_2);
    floorButtons[3] = new ButtonDriver(PIN_FLOOR_BTN_3);

    // Initialize floor switches
    floorSwitches[0] = new SwitchDriver(PIN_FLOOR_SWITCH_0);
    floorSwitches[1] = new SwitchDriver(PIN_FLOOR_SWITCH_1);
    floorSwitches[2] = new SwitchDriver(PIN_FLOOR_SWITCH_2);
    floorSwitches[3] = new SwitchDriver(PIN_FLOOR_SWITCH_3);

    for (int i = 0; i < FLOOR_COUNT; i++) {
        floorButtons[i]->onPress([this, i]() { goToFloor(i); });
    }

    // Initialize call button
    callButton = new ButtonDriver(PIN_CALL_BTN);

    // Turn on floor 0 LED and enter initial idle state
    floorLeds[currentFloor]->on();
    setState(new IdleState(this));
}

void LiftController::update()
{
    for (int i = 0; i < FLOOR_COUNT; i++) floorButtons[i]->update();
    for (int i = 0; i < FLOOR_COUNT; i++) floorSwitches[i]->update();
    callButton->update();

    if (currentState) {
        ElevatorState* next = currentState->update();
        if (next) setState(next);
    }
}

void LiftController::goToFloor(int floor)
{
    if (floor < 0 || floor >= FLOOR_COUNT) return;
    if (isMoving || doorsInMotion) return;

    pendingFloor = floor;

    if (doorsOpen) {
        setState(new CloseDoorsState(this));
    } else {
        setState(new OpenDoorsState(this));
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
    if (currentState) {
        currentState->onExit();
        delete currentState;
    }
    currentState = newState;
    if (currentState) currentState->onEnter();
}

void LiftController::setDoorStatus(DoorStatus status)
{
    doorsOpen = (status == DoorStatus::Open);
    doorStatusLeds[0]->off();
    doorStatusLeds[1]->off();
    doorStatusLeds[2]->off();
    switch (status) {
        case DoorStatus::Open:   doorStatusLeds[0]->on(); break;
        case DoorStatus::Closed: doorStatusLeds[1]->on(); break;
        case DoorStatus::Moving: doorStatusLeds[2]->on(); break;
    }
}

void LiftController::turnOnFloorLed(int floor)
{
    for (int i = 0; i < FLOOR_COUNT; i++) floorLeds[i]->off();
    if (floor >= 0 && floor < FLOOR_COUNT) {
        floorLeds[floor]->on();
        currentFloor = floor;
    }
}