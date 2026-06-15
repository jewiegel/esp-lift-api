#pragma once

constexpr int FLOOR_COUNT = 3;

// Floor LEDs
constexpr int PIN_FLOOR_LED_0 = 9;
constexpr int PIN_FLOOR_LED_1 = 10;
constexpr int PIN_FLOOR_LED_2 = 11;
constexpr int PIN_FLOOR_LED_3 = 12;

// Door status LEDs
constexpr int PIN_DOOR_LED_OPEN   = 17;
constexpr int PIN_DOOR_LED_CLOSED = 18;
constexpr int PIN_DOOR_LED_MOVING = 8;

// Floor buttons (inside lift)
constexpr int PIN_FLOOR_BTN_0 = 40;
constexpr int PIN_FLOOR_BTN_1 = 41;
constexpr int PIN_FLOOR_BTN_2 = 42;
constexpr int PIN_FLOOR_BTN_3 = 0;

// Floor switches (detecting lift at floor)
constexpr int PIN_FLOOR_SWITCH_0 = 8;
constexpr int PIN_FLOOR_SWITCH_1 = 17;
constexpr int PIN_FLOOR_SWITCH_2 = 16;
constexpr int PIN_FLOOR_SWITCH_3 = 47; 

// Binary signal for moving lift
constexpr int MOVING_LIFT_UP = 47;
constexpr int MOVING_LIFT_DOWN = 48;

// Call button
constexpr int PIN_CALL_BTN = 6;
