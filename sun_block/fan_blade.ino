#include "fan_blade.h"
#include "esp8266.h"

Fan_blade fan_blades[NUM_BLADES];


/*
void setup() {
    Serial.begin(115200);
    initalize_fan_blades();
}

void loop() {
    if(is_blade_at_set_point(0)) {
        update_set_point(0, angle_test[counter]);
        counter++;
        if (counter == 2) {
            counter = 0;
        }   
    }

    debug_blade(0);

    update_all_blades();

}
*/

void set_blade_angle_direct(uint8_t id, uint8_t angle) {
    Fan_blade *blade = get_blade(id);
    blade->set_point = angle;
    blade->servo.write(angle);
    blade->current_angle = angle;
}

void update_all_blades() {
    for (int i = 0; i < NUM_BLADES; i++) {
        if (is_blade_at_set_point(i)) {
            // we are at set point, no need to continue

        } else {
            // not at setpoint
            Fan_blade *blade = get_blade(i);
            int16_t delta = blade->set_point - blade->current_angle;
            if (delta > 0) {
                // move up
                blade->current_angle += STEP_SIZE;
            } else {
                // move down
                blade->current_angle -= STEP_SIZE;
            }
            blade->servo.write(blade->current_angle);
        }
    }
    delay(DELAY);
}

void update_set_point(uint8_t id, uint8_t angle) {
    fan_blades[id].set_point = angle;
}

bool is_blade_at_set_point(uint8_t id) {
    Fan_blade *blade = get_blade(id);
    return blade->set_point == blade->current_angle;
}

Fan_blade * get_blade(uint8_t id) {
    return &fan_blades[id];
}

void initalize_fan_blades() {
    for(int i = 0; i < NUM_BLADES; i++) {
        Fan_blade * blade = get_blade(i);
        blade->pin = pin[i];
        blade->servo.attach(blade->pin, MIN_ANGLE_MS, MAX_ANGLE_MS);
        set_blade_angle_direct(i, 0);
    }
}

void debug_blade(uint8_t id) {
    Fan_blade * blade = get_blade(id);
    Serial.println("------------------");
    Serial.print("Blade: ");
    Serial.print(id);
    Serial.print(" pin: ");
    Serial.println(blade->pin);
    Serial.print("  set point: ");
    Serial.println(blade->set_point);
    Serial.print("  current_angle: ");
    Serial.println(blade->current_angle);
    Serial.print("  delta: ");
    Serial.println(blade->set_point - blade->current_angle);
}