#pragma once

#include "PinConfig.h"
#include "Hardware/Button/ButtonDriver.h"
#include "Hardware/Button/IButtonDriver.h"
#include "Hardware/Switch/SwitchDriver.h"
#include "Hardware/Switch/ISwitchDriver.h"
#include "Hardware/LiftMotor/LiftMotorDriver.h"
#include "Hardware/LiftMotor/DoorMotorDriver.h"
#include "Hardware/LiftMotor/IBinaryMotorDriver.h"

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
    volatile bool robotWaitFloors[FLOOR_COUNT] = {};
    ElevatorState* currentState = nullptr;
    LiftCommandScheduler* scheduler;

    IButtonDriver* floorButtons[FLOOR_COUNT];
    ISwitchDriver* floorSwitches[FLOOR_COUNT];
    IButtonDriver* resetButton;
    IButtonDriver* callButton;
    IBinaryMotorDriver* motor;
    IBinaryMotorDriver* doorMotor;

public:
    LiftController(LiftCommandScheduler* scheduler);
    ~LiftController();
    void setup();
    void update();
    void goToFloor(int floor);
    void moveToFloor(int floor);
    void resetLift();
    void openDoors();
    void closeDoors();
    void setState(ElevatorState* newState);
    void setDoorStatus(DoorStatus status);
    void setCurrentFloor(int floor);
    void motorUp();
    void motorDown();
    void stopMotor();
    void openDoor();
    void closeDoor();
    void stopDoor();
    void setIsMoving(bool moving) { isMoving = moving; }
    void setDoorsInMotion(bool inMotion) { doorsInMotion = inMotion; }
    void setPendingFloor(int floor) { pendingFloor = floor; }
    int getPendingFloor() const { return pendingFloor; }
    ISwitchDriver* getFloorSwitch(int floor) { return floorSwitches[floor]; }
    int getCurrentFloor() const { return currentFloor; }
    bool areDoorsOpen() const { return doorsOpen; }
    bool areDoorsInMotion() const { return doorsInMotion; }
    bool getIsMoving() const { return isMoving; }

    // Robot waiting: a floor is registered up front (independent of the FIFO
    // queue); on arrival there the lift holds until the robot signals 'ready'.
    void registerRobotWait(int floor);
    void robotReady();
    bool isWaitingForRobotHere() const;
};
