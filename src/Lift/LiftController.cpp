#include "LiftController.h"

LiftController::LiftController()
{
}

LiftController::~LiftController()
{
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

    for (int i = 0; i < FLOOR_COUNT; i++) {
        floorButtons[i]->onPress([this, i]() { goToFloor(i); });
    }

    // Initialize call button
    callButton = new ButtonDriver(PIN_CALL_BTN);

    // Set initial state
    goToFloor(0);
}

void LiftController::update()
{
    for (int i = 0; i < FLOOR_COUNT; i++) floorButtons[i]->update();
    callButton->update();
}

void LiftController::goToFloor(int floor)
{
    if (floor == currentFloor || floor < 0 || floor > FLOOR_COUNT) return;

    floorLeds[currentFloor]->off();
    currentFloor = floor;
    floorLeds[currentFloor]->on();

    Serial.println("Going to floor: " + String(currentFloor));
}

void LiftController::openDoors()
{
    // Logic to open the lift doors
}

void LiftController::closeDoors()
{
    // Logic to close the lift doors
}