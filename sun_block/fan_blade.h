// BLADE_RELAY_PIN (pin[NUM_PIN-3]) // TX1_D9

#ifndef FAN_BLADE_H
#define FAN_BLADE_H

#include <Arduino.h>
#include <Servo.h>

#define STEP_SIZE (1)
#define NUM_BLADES (5)
#define MIN_ANGLE_MS (500)  // 0 degrees
#define MAX_ANGLE_MS (2500) // 180 degrees
#define DELAY 100

#define BLADE_RELAY_PIN (pin[NUM_PIN - 3]) // TX1_D9

struct Fan_blade
{
    uint8_t pin;
    Servo servo;
    uint16_t set_point;
    uint16_t current_angle;
};

// Set blade to given angle
void blade__set_angle_direct(uint8_t id, uint8_t angle);

// Call in loop function, slowly move towards set point
void blade__update_all();

// Set setpoint of given blade
void blade__update_set_point(uint8_t id, uint8_t angle);

// Call during setup function
void blade__initalize();

// return true if blade is at set point
bool blade__is_at_set_point(uint8_t id);

// print blade data to serial monitor
void blade__debug_print(uint8_t id);

uint16_t blade__get_current_angle(uint8_t id);
uint16_t blade__get_set_point(uint8_t id);

#endif
