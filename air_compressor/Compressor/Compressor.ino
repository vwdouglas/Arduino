




/*pressure 0 psi = 0 volts 
//Pressure 150 psi = 5 Volts 
turn off the compressure at 1010 ~ 140psi

For Mitsubishi FR-700 inverter
connect pin 2 to RL
connect pin 3 to RM 
connect pin 4 to RH
Connect pin 5 to STF
Connect SD to the Compressure side of the relays 

Power Switch
Connrct pin 6 to PSW
connect GND to PSW

Display connect to arduino pins A4(SDA),A5(SCL) and 5V, Ground
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

const int BUTTON_PIN = 6;

int analogPin = A0;        // pressure sensor (middle terminal) connected to analog pin 1 outside leads to ground and +5V
double inPutPressure = 0;  //Pressure gage
double lowPressure = 95;
double medPressure = 120;
//int highPressure = 900;
double offPressure = 140;
double onPressure = 100;
bool compressureState = true;  // true = on   false = off
//bool compressureStateOn = true;
float displayPressure = 0;
float const multplyerForPSI = .1470588;

void setup() {
  pinMode(6, INPUT_PULLUP);
  pinMode(2, OUTPUT);  // sets the digital pin 2 as output Set freek drive on low
  pinMode(3, OUTPUT);  // sets the digital pin 3 as output Set freek drive on med-low
  pinMode(4, OUTPUT);  // sets the digital pin 4 as output Set freek drive on high
  pinMode(5, OUTPUT);  // sets the digital pin 5 as output turn on freek drive.

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  inPutPressure = 0;

  // Display Pressure Section 150psi = 1020
  displayPressure = inPutPressure * 150 / 1020;


  lcd.init();  // initialize the lcd

  lcd.backlight();
}

void loop() {
  int powerSW = digitalRead(BUTTON_PIN);  //power switch

 
  // Power switch
  //int powerSW = digitalRead(BUTTON_PIN);  //power switch
  if (powerSW == LOW) {
    // lcd.clear();
    //lcd.setCursor(3, 3);
    //lcd.print("POWER OFF");
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  //Wiring Setup
   // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("D2=RL D3=RM D4=RH");
    lcd.setCursor(1, 0);
    lcd.print("D5=STF ");
    lcd.setCursor(2, 0);
    lcd.print("SD to all relays");
    lcd.setCursor(3, 0);
    lcd.print("PW~D6=PSW / GND=PSW");
      
        return;
  }


  // Display Pressure Section 150psi = 1020
  lcd.clear();
  lcd.setCursor(0, 0);                // move cursor to   (0, 0)
  lcd.print("Doug's AirCompressor");  // print message at (0, 0)
  lcd.setCursor(0, 1);                // move cursor to   (2, 1)
  lcd.print("Stop = ");               // print message at (2, 1)
  lcd.print(offPressure);
  lcd.setCursor(0, 2);
  lcd.print("Start = ");
  lcd.print(onPressure);
  lcd.setCursor(0, 3);  // move cursor to   (0, 2)
  lcd.print("Pressure ");
  inPutPressure = analogRead(analogPin) * multplyerForPSI;
  displayPressure = (inPutPressure);
  //lcd.setCursor(8, 3);  // move cursor to   (10, 3)
  lcd.print(displayPressure);
  lcd.print(" PSI  ");
  //lcd.setCursor(10, 3);  // move cursor to   (3, 1)
  //lcd.print(inPutPressure);
  //lcd.print("    ");
  delay(500);

  // Compressure contral section

  if (inPutPressure >= offPressure) {
    compressureState = false;  // true = on "Low pressure"   false = off "High pressure"
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if (!compressureState) {  // true = on "Low pressure"   false = off "High pressure"
    if (inPutPressure <= onPressure) {
      compressureState = true;
    }
  }
  if (compressureState) {
    if (inPutPressure > medPressure) {  //LOw Pressure
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (medPressure > inPutPressure && inPutPressure >= lowPressure) {  //Mid Pressure
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (inPutPressure < lowPressure) {  //High Pressure (low pressure)
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
    }
  }
}
