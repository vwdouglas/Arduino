#include "fan_blade.h"
#include "esp8266.h"
#include "OTA.h"
#include <Arduino.h>


void setup() {
    Serial.begin(BAUD_RATE);
    setup_OTA();
    initalize_fan_blades();
}

void loop() {

    //todo 

    update_all_blades();

}