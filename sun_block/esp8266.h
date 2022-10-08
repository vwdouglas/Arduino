#ifndef ESP8226_H
#define ESP8226_H

#include <Arduino.h>

//safe pins
#define D15_SCL    (5)
#define D14_SDA    (4)
#define D13_SCK    (14)
#define D12_MISO   (12)
#define D11_MOSI   (13)
#define D8         (0)
#define D2         (16)
// used at boot, safe after
#define TX1_D9     (2)

#define NUM_PIN (8)//(8)

uint8_t pin[NUM_PIN] = {D15_SCL, D14_SDA, D13_SCK, D12_MISO, D11_MOSI, TX1_D9, D8, D2};


#define BAUD_RATE (115200)

#define OFF (HIGH)
#define ON  (LOW)

void esp8266__goto_sleep_now();

#endif