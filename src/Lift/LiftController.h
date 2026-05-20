#pragma once

#include "PinConfig.h"
#include "Hardware/Button/ButtonDriver.h"
#include "Hardware/Button/IButtonDriver.h"
#include "Hardware/Led/LedDriver.h"
#include "Hardware/Led/ILedDriver.h"
#include "LiftStates/IElevatorState.h"

enum class DoorStatus { Open, Closed, Moving };

class LiftController
{
private:
    int currentFloor = 0;
    ElevatorState* currentState = nullptr;

    ILedDriver*    floorLeds[4];
    ILedDriver*    doorStatusLeds[3];
    IButtonDriver* floorButtons[4];
    IButtonDriver* callButton;

public:
    LiftController();
    ~LiftController();
    void setup();
    void update();
    void goToFloor(int floor);
    void openDoors();
    void closeDoors();
    void setState(ElevatorState* newState);
    void setDoorStatus(DoorStatus status);
    int getCurrentFloor() const { return currentFloor; }
};
