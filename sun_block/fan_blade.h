#ifndef FAN_BLADE_H
#define FAN_BLADE_H

#include <Arduino.h>
#include <Servo.h>

#define STEP_SIZE 1
#define NUM_BLADES 2
#define MIN_ANGLE_MS 500 // 0 degrees
#define MAX_ANGLE_MS 2500 // 180 degrees
#define DELAY 0

struct Fan_blade {
    uint8_t pin;
    Servo servo;
    uint16_t set_point;
    uint16_t current_angle;
};

// Set blade to given angle
void set_blade_angle_direct(uint8_t id, uint8_t angle);

// Call in loop function, slowly move towards set point
void update_all_blades();

// Set setpoint of given blade
void update_set_point(uint8_t id, uint8_t angle);

// Call during setup function
void initalize_fan_blades();

// return true if blade is at set point
bool is_blade_at_set_point(uint8_t id);

//print blade data to serial monitor
void debug_blade(uint8_t id);
#endif