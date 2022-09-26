#include "fan_blade.h"
#include "esp8266.h"
#include "OTA.h"
#include <Arduino.h>
#include "wench.h"
#include "MQTT.h"


void setup() {
    Serial.begin(BAUD_RATE);
    setup_OTA();
    mqtt__setup(process_mqtt_message);
    blade__initalize();
}

void loop() {
    
    if(!mqtt__is_connected()) {
        mqtt__reconnect();
    }

    mqtt__loop();
    blade__update_all();

    if (can_sleep_now()) {
        esp8266__goto_sleep_now();
    }

}

/* callback when we get an mqtt msg */
void process_mqtt_message(char *topic, byte *payload, unsigned int length) {

    String string;
    for (int i = 0; i < length; i++) {
        string += ((char)payload[i]);
    }

    if (0 == strcmp(topic, topic_wench_up)) {
        wench__move_up();
    }
    else if (0 == strcmp(topic, topic_wench_down)) {
        wench__move_down();
    }
    else if (0 == strcmp(topic, topic_blade[6])) {
        //set all blades
        for (uint8_t id = 0; id < NUM_BLADES; id++) {
            blade__update_set_point(id, string.toInt());
#if (1 == CASCADE_ALL_MOVEMENT) 
            delay(CASCADE_DELAY);
#endif
        }

    } else {
        // check each topic for blade id
        for (uint8_t id = 0; id < NUM_BLADES; id++) {
            if (strcmp(topic, topic_blade[id]) == 0) {
                blade__update_set_point(id, string.toInt());
            }
        }
    }

}

/* decide if going to sleep could happen */
bool can_sleep_now() {
    for (int i = 0; i < NUM_BLADES; i++) {
        if (!blade__is_at_set_point(i)) {
            return false;
        }
    }

    return true;
}

