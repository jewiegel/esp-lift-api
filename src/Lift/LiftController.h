#pragma once

#include "PinConfig.h"
#include "Hardware/Button/ButtonDriver.h"
#include "Hardware/Button/IButtonDriver.h"
#include "Hardware/Led/LedDriver.h"
#include "Hardware/Led/ILedDriver.h"
#include "Hardware/Switch/SwitchDriver.h"
#include "Hardware/Switch/ISwitchDriver.h"

#include "LiftStates/IElevatorState.h"

class LiftCommandScheduler;

enum class DoorStatus { Open, Closed, Moving };

class LiftController
{
private:
    int currentFloor = 0;
    int pendingFloor = -1;
    bool doorsOpen = false;
    bool doorsInMotion = false;
    bool isMoving = false;
    ElevatorState* currentState = nullptr;
    LiftCommandScheduler* scheduler;

    ILedDriver*    floorLeds[FLOOR_COUNT];
    ILedDriver*    doorStatusLeds[3];
    IButtonDriver* floorButtons[FLOOR_COUNT];
    ISwitchDriver* floorSwitches[FLOOR_COUNT];
    IButtonDriver* callButton;

public:
    LiftController(LiftCommandScheduler* scheduler);
    ~LiftController();
    void setup();
    void update();
    void goToFloor(int floor);
    void moveToFloor(int floor);
    void openDoors();
    void closeDoors();
    void setState(ElevatorState* newState);
    void setDoorStatus(DoorStatus status);
    void turnOnFloorLed(int floor);
    void setIsMoving(bool moving) { isMoving = moving; }
    void setDoorsInMotion(bool inMotion) { doorsInMotion = inMotion; }
    void setPendingFloor(int floor) { pendingFloor = floor; }
    int getPendingFloor() const { return pendingFloor; }
    ISwitchDriver* getFloorSwitch(int floor) { return floorSwitches[floor]; }
    int getCurrentFloor() const { return currentFloor; }
    bool areDoorsOpen() const { return doorsOpen; }
};
