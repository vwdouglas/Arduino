#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>

#define MQTT_PORT (1883)

const char *mqtt_server = "192.168.0.44"; // IP Broker MQTT
const char *topic_blade[7] = {
    &*"MBR/servo/blade1", // MQTT topic for blade 1
    &*"MBR/servo/blade2", // MQTT topic for blade 2
    &*"MBR/servo/blade3", // MQTT topic for blade 3
    &*"MBR/servo/blade4", // MQTT topic for blade 4
    &*"MBR/servo/blade5", // MQTT topic for blade 5
    &*"MBR/servo/blade6", // MQTT topic for blade 6
};

const char *topic_wench_up = "MBR/wench/up";     // MQTT topic to wench up
const char *topic_wench_down = "MBR/wench/down"; // MQTT topic to wench down

typedef void (*Callback)(char *topic, byte *payload, unsigned int length);

void mqtt__setup(Callback callback);

bool mqtt__is_connected();

void mqtt__reconnect();

void mqtt__loop();

#endif

