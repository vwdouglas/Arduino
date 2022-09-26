#ifndef WENCH_H
#define WENCH_H

#include "esp8266.h"
#include <Arduino.h>

#define DELAY_DOWN (2000)
#define DELAY_UP   (2000)

#define WENCH_UP_PIN (pin[NUM_PIN-2]) //D2
#define WENCH_DOWN_PIN (pin[NUM_PIN-1]) //D8

void wench__setup();

void wench__move_up();

void wench__move_down();


#endif