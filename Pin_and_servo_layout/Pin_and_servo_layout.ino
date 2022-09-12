/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#include <Servo.h>
Servo myservo;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  myservo.attach(D3);
  myservo2.attach(D4);
  myservo3.attach(D5);
  myservo4.attach(D6);
  myservo4.attach(D7);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D0, OUTPUT);
   pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D0, LOW);   // turn the LED on (HIGH is the voltage level)
Serial.println("D0");
  delay(100);// wait for a second
   digitalWrite(D0, HIGH);    // turn the LED off by making the voltage LOW
  delay(400); // wait for a second

   digitalWrite(D1, LOW);   // turn the LED on (HIGH is the voltage level)
Serial.println("D1");
  delay(100);// wait for a second
   digitalWrite(D1, HIGH);    // turn the LED off by making the voltage LOW
  delay(400); // wait for a second
  digitalWrite(D2, LOW);   // turn the LED on (HIGH is the voltage level)
Serial.println("D2");
  delay(100);// wait for a second
   digitalWrite(D2, HIGH);    // turn the LED off by making the voltage LOW
  delay(500); // wait for a second
  // Servo 1
  myservo.write(10);
  Serial.println("move to 10");
  delay(400);
myservo.write(180);
Serial.println("Move to 180");
  delay(2000);
//  Servo2
   myservo2.write(0);
  Serial.println("#2 move to 10");
  delay(400);
myservo2.write(180);
Serial.println("#2 Move to 180");
  delay(2000);
  //  Servo3
   myservo3.write(0);
  Serial.println("#3 move to 10");
  delay(400);
myservo3.write(180);
Serial.println("#3 Move to 180");
  delay(2000);
   //  Servo4
   myservo4.write(0);
  Serial.println("#4 move to 10");
  delay(400);
myservo4.write(180);
Serial.println("#4 Move to 180");
  delay(2000);
   //  Servo5
   myservo5.write(0);
  Serial.println("#5 move to 10");
  delay(400);
myservo4.write(180);
Serial.println("#5 Move to 180");
  delay(2    l000);
}
