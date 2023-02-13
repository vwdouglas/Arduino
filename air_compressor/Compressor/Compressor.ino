
/*pressure 0 psi = 0 volts 
//Pressure 150 psi = 5 Volts 
turn off the compressure at 1010 ~ 140psi

For Mitsubishi FR-700 inverter
connect Relay 1 to RL    
connect Relay 2 to RM  
connect Relay 3 to RH 
Connect Relay 5 to STF
Connect SD to the Compressure side of the relays 

Power Switch
Connect a switch from 5v to 10K res. to pin 10 for on. Pin 10 to gnd for off

Pressure Sensor 5V, gnd, A1

Display connect to arduino pins A4(SDA),A5(SCL) and 5V, Ground
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

const int swpin = 10;
int lowSpeed = 7;    // Relay 1
int medSpeed = 6;    // Relay 2
int highSpeed = 5;   // Relay 3
int startFWD = 4;    // Relay 4
int analogPin = A0;  // pressure sensor (middle terminal) connected to analog pin 1 outside leads to ground and +5V
int i;
float inPutPressure = 0;  //Pressure gage
double lowPressure = 95;
double medPressure = 120;
double offPressure = 135;
double onPressure = 100;
bool compressureState = true;  // true = on   false = off
//bool compressureStateOn = true;
float displayPressure = 0;
float const multplyerForPSI = .1470588;
int powerSW;  //power switch
const int sampleSize = 10;
double readPressure[sampleSize];
int pressureCounter = 0;
double arrayTotal = 0;

void setup() {

  memset(readPressure, 0, sizeof(readPressure[sampleSize]));

  pinMode(swpin, INPUT);       //power button
  pinMode(lowSpeed, OUTPUT);   // sets the digital pin 7 as output Set freek drive on low
  pinMode(medSpeed, OUTPUT);   // sets the digital pin 6 as output Set freek drive on med-low
  pinMode(highSpeed, OUTPUT);  // sets the digital pin 5 as output Set freek drive on high
  pinMode(startFWD, OUTPUT);   // sets the digital pin 4 as output turn on freek drive.

  digitalWrite(lowSpeed, LOW);
  digitalWrite(medSpeed, LOW);
  digitalWrite(highSpeed, LOW);
  digitalWrite(startFWD, HIGH);
  powerSW = digitalRead(swpin);  //power switch
  Serial.begin(9600);
  Serial.print("button  ");
  Serial.println(powerSW);
  // Display Pressure Section 150psi = 1020
  displayPressure = inPutPressure * 150 / 1020;


  lcd.init();  // initialize the lcd

  lcd.backlight();
}
void displaySetup() {
  // Display Pressure Section 150psi = kk
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
  delay(500);
}

void displayWrite() {

  displayPressure = (inPutPressure);
  //lcd.setCursor(8, 3);  // move cursor to   (10, 3)
  lcd.print(displayPressure);
  lcd.print(" PSI  ");
  //lcd.setCursor(10, 3);  // move cursor to   (3, 1)
  //lcd.print(inPutPressure);
  //lcd.print("    ");
  delay(500);
}

void powerOff() {
  // Power switch
  //int powerSW = digitalRead(BUTTON_PIN);  //power switch

  // lcd.clear();
  //lcd.setCursor(3, 3);
  //lcd.print("POWER OFF");
  digitalWrite(lowSpeed, LOW);
  digitalWrite(medSpeed, LOW);
  digitalWrite(highSpeed, LOW);
  digitalWrite(startFWD, LOW);
  //Wiring Setup
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("D4=RL D7=RM D8=RH");
  lcd.setCursor(0, 1);
  lcd.print("D12=STF ");
  lcd.setCursor(0, 2);
  lcd.print("SD to all relays");
  lcd.setCursor(0, 3);
  lcd.print("PW~D6=PSW / GND=PSW");
  delay(500);
}

void loop() {
  powerSW = digitalRead(swpin);  //power switch
  Serial.print("button  ");
  Serial.println(powerSW);
  if (powerSW == LOW) {
    powerOff();
  } else if (powerSW == HIGH) {
    displaySetup();
  }
  //while (!compressureState)  {
  displayWrite();

  // Compressure contral section
  pressureCounter++;
  if (pressureCounter > sampleSize) {
    pressureCounter = 1;
    Serial.println();
    Serial.print("inside Else pressureCounter should be 0 = ");
    Serial.println(pressureCounter);
  }
  Serial.print("outside else Pressure Counter = ");
  Serial.println(pressureCounter);

  readPressure[pressureCounter - 1] = analogRead(analogPin) * multplyerForPSI;
  inPutPressure = 0;

  Serial.print("array value= ");
  arrayTotal = 0;
  // Avrage out inputPressure
  for (int ii = 1; ii < sampleSize + 1; ii++) {
    arrayTotal += readPressure[ii - 1];


    Serial.print(readPressure[ii - 1]);
    Serial.print(". ");
  }  //end for loop

  inPutPressure = arrayTotal / sampleSize;

  if (inPutPressure >= offPressure) {
    compressureState = false;  // true = on "Low pressure"   false = off "High pressure"
    digitalWrite(lowSpeed, LOW);
    digitalWrite(medSpeed, LOW);
    digitalWrite(highSpeed, LOW);
    digitalWrite(startFWD, HIGH);
  }
  if (!compressureState) {  // true = on "Low pressure"   false = off "High pressure"
    if (inPutPressure <= onPressure) {
      compressureState = true;
    }
  }
  if (compressureState) {
    if (inPutPressure > medPressure) {  //High Pressure/ Low speed
      digitalWrite(lowSpeed, HIGH);
      digitalWrite(medSpeed, LOW);
      digitalWrite(highSpeed, LOW);
      digitalWrite(startFWD, HIGH);
      Serial.println();
      Serial.print("High Pressure stf= ");
      Serial.println(startFWD);
      Serial.println();
      delay(10);
    } else if (medPressure > inPutPressure && inPutPressure >= lowPressure) {  //Mid Pressure / med speed
      digitalWrite(lowSpeed, LOW);
      digitalWrite(medSpeed, HIGH);
      digitalWrite(highSpeed, LOW);
      digitalWrite(startFWD, HIGH);
      Serial.println();
      Serial.print("Med Pressure stf= ");
      Serial.println(startFWD);
      Serial.println();
      delay(500);
    } else if (inPutPressure < lowPressure) {  //High Speed (low pressure)
      digitalWrite(lowSpeed, LOW);
      digitalWrite(medSpeed, LOW);
      digitalWrite(highSpeed, HIGH);
      digitalWrite(startFWD, HIGH);
      delay(1000);
      Serial.println();
      Serial.print("Low Pressure stf= ");
      Serial.println(startFWD);
      Serial.println();
    }
  }
}
