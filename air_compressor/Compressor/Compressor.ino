#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);
int analogPin = A0;  // pressure sensor (middle terminal) connected to analog pin 1 outside leads to ground and +5V
int inPutPressure;   //Pressure gage


void setup() {
  pinMode(2, OUTPUT);  // sets the digital pin 2 as output Set freek drive on low
  pinMode(3, OUTPUT);  // sets the digital pin 3 as output Set freek drive on med-low
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  inPutPressure = 0;
  lcd.init();  // initialize the lcd

  lcd.backlight();
  lcd.setCursor(0, 0);           // move cursor to   (0, 0)
  lcd.print("Doug's Pre-1952");  // print message at (0, 0)
  lcd.setCursor(2, 1);           // move cursor to   (2, 1)
  lcd.print("AirCompressor");    // print message at (2, 1)
  lcd.setCursor(0, 2);           // move cursor to   (0, 2)
  lcd.print("Pressure  ");
}

void loop() {
  inPutPressure = analogRead(analogPin);
  lcd.setCursor(10, 2);  // move cursor to   (3, 1)
  lcd.print(inPutPressure);
  lcd.print("    ");

  if (inPutPressure > 800) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (inPutPressure < 799 and inPutPressure > 500) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (inPutPressure < 499 and inPutPressure > 100) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
}
