#pragma once

#include "PinConfig.h"
#include "Hardware/Button/ButtonDriver.h"
#include "Hardware/Button/IButtonDriver.h"
#include "Hardware/Led/LedDriver.h"
#include "Hardware/Led/ILedDriver.h"

class LiftController
{
private:
    int currentFloor = 0;

    // Interface pointers — used throughout the class
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
};
