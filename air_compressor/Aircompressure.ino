#include <Arduino.h>

int sensorPin = A0;    // select the input pin for the
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  int CurrentPressure = 0;
  int sensorPin = A0;    // select the input pin for the input pressure


}

void loop() {
  // read the value from the sensor:
  CurrentPressure = analogRead(sensorPin);
  
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds: