#include "wench.h"
#include "esp8266.h"


void wench__setup()
{
  Serial.println("Setup Wench");
  pinMode(WENCH_DOWN_PIN, OUTPUT);
  digitalWrite(WENCH_DOWN_PIN, OFF);
  pinMode(WENCH_UP_PIN, OUTPUT);
  digitalWrite(WENCH_UP_PIN, OFF);
}

void wench__move_up()
{
  Serial.println("Setup Wench up");
        digitalWrite(WENCH_UP_PIN, ON);
        delay(DELAY_UP);
        digitalWrite(WENCH_UP_PIN, OFF);
        Serial.println("Wench up ");
}



void wench__move_down()
{
  Serial.println("Wench down ");
  digitalWrite(WENCH_DOWN_PIN, ON);
  delay(DELAY_DOWN);
  digitalWrite(WENCH_DOWN_PIN, OFF);
 
}
