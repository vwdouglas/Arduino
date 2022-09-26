#include "esp8266.h"

// sleep fuction, for now just let us know sleep is possible
void esp8266__goto_sleep_now() {
    static uint16_t sleep_counter = 0;
    sleep_counter++;
    if (0 == sleep_counter) {
        Serial.println("I could sleep now..");
    };
}
