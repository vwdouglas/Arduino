#include "fan_blade.h"
#include "esp8266.h"

Fan_blade fan_blades[NUM_BLADES];

void blade__set_angle_direct(uint8_t id, uint8_t angle)
{
    Fan_blade *blade = get_blade(id);
    blade->set_point = angle;
    blade->servo.write(angle);
    blade->current_angle = angle;
}

void blade__update_all()
{
    if (!blade__is_all_at_setpoint())
    {
        enable_servo_relay();
        for (int i = 0; i < NUM_BLADES; i++)
        {
            if (blade__is_at_set_point(i))
            {
                // we are at set point, no need to continue
            }
            else
            {
                // not at setpoint
                Fan_blade *blade = get_blade(i);
                int16_t delta = blade->set_point - blade->current_angle;
                if (delta > 0)
                {
                    // move up
                    blade->current_angle += STEP_SIZE;
                }
                else
                {
                    // move down
                    blade->current_angle -= STEP_SIZE;
                }
                blade->servo.write(blade->current_angle);
            }
        }
        delay(DELAY);
    }
    else
    {
        disable_servo_relay();
    }
}

void blade__update_set_point(uint8_t id, uint8_t angle)
{
    fan_blades[id].set_point = angle;
}

bool blade__is_at_set_point(uint8_t id)
{
    Fan_blade *blade = get_blade(id);
    return blade->set_point == blade->current_angle;
}

bool blade__is_all_at_setpoint()
{
    for (uint8_t id = 0; id < NUM_BLADES; id++)
    {
        if (!blade__is_at_set_point(id))
        {
            return false;
        }
    }

    return true;
}

Fan_blade *get_blade(uint8_t id)
{
    return &fan_blades[id];
}

void blade__initalize()
{

    pinMode(BLADE_RELAY_PIN, OUTPUT);

    for (int i = 0; i < NUM_BLADES; i++)
    {
        Fan_blade *blade = get_blade(i);
        blade->pin = pin[i];
        blade->servo.attach(blade->pin, MIN_ANGLE_MS, MAX_ANGLE_MS);
        blade__set_angle_direct(i, 0);
    }
}

uint16_t blade__get_current_angle(uint8_t id)
{
    return get_blade(id)->current_angle;
}

uint16_t blade__get_set_point(uint8_t id)
{
    return get_blade(id)->set_point;
}

void enable_servo_relay()
{
    digitalWrite(BLADE_RELAY_PIN, ON);
}

void disable_servo_relay()
{
    digitalWrite(BLADE_RELAY_PIN, OFF);
}
void blade__debug_print(uint8_t id)
{
    Fan_blade *blade = get_blade(id);
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