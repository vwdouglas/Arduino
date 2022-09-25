#include "wench.h"

void setup_wench() {
  pinMode(WENCH_DOWN_PIN, OUTPUT);
  digitalWrite(WENCH_DOWN_PIN, HIGH);

  pinMode(WENCH_UP_PIN, OUTPUT);
  digitalWrite(WENCH_UP_PIN, HIGH);
}

void move_up() {
    Serial.println("Wench up ");
    digitalWrite(WENCH_UP_PIN, LOW);
    delay(DELAY_UP);
    digitalWrite(WENCH_UP_PIN, HIGH);
}

void move_down() {
    Serial.println("Wench down ");
    digitalWrite(WENCH_DOWN_PIN, LOW);
    delay(DELAY_DOWN);
    digitalWrite(WENCH_DOWN_PIN, HIGH);

}

