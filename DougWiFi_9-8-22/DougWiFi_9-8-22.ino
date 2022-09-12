


//*****Doug*******
//Wench up D14
//Wench Down D15
//Blade 1-5 =>D2-D6
//Relay to work servo D7
//Relay unused xxxx
// MQTT Protocall
// Topic = servo/bladex = pin (D"x+1")


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Servo.h>
#include <SlowMotionServo.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>

WiFiClient espClient;
PubSubClient client(espClient);

SMSSmooth blade[7];// Servo with linear trajectory 
float target = 0.0;

//Servo blade[7]; //= {   // Declares Servos
// Paramètre WiFi, MQTT - WiFi, MQTT parameters
const char *ssid = ".";                    // WiFi SSID
const char *password = "m31J16d3R21";      // WiFi Password
const char *mqtt_server = "192.168.0.44"; // IP Broker MQTT
const char *topic_blade[7] = {
    &*"MBR/servo/blade1", // MQTT topic for blade 1
    &*"MBR/servo/blade2", // MQTT topic for blade 2
    &*"MBR/servo/blade3", // MQTT topic for blade 3
    &*"MBR/servo/blade4", // MQTT topic for blade 4
    &*"MBR/servo/blade5", // MQTT topic for blade 5
    &*"MBR/servo/blade6", // MQTT topic for blade 6
//    &*"MBR/servo/blade7", // MQTT topic for blade 7
    &*"MBR/servo/all"     // MQTT topic to move all blades
};

const char *topic_wench_up = "MBR/wench/up";     // MQTT topic to wench up
const char *topic_wench_down = "MBR/wench/down"; // MQTT topic to wench down
//int PreviousPos=0;


long lastMsg = 0;
char msg[50];
int value = 0;

void setup()
{
 
  ArduinoOTA.onStart([]()
{
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]()
  {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) 
  {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) 
  {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(D14, OUTPUT);    //Wench
  digitalWrite(D14, HIGH);
  // badline
  pinMode(D15, OUTPUT);    //Wench
  digitalWrite(D15, HIGH);
  pinMode(D7, OUTPUT);    //Relay for Servos
  digitalWrite(D7, HIGH);


    Serial.begin(115200);
  Serial.println("End   setup");

/* 
Old servo setup

  blade[1].attach(D2);
  blade[2].attach(D3);
  blade[3].attach(D4);
  blade[4].attach(D5);
  blade[5].attach(D6);
*/
 
 //New servo setup slowmotion 
  blade[1].setInitialPosition(target);
  blade[1].setMinMax(700, 2000);
  blade[1].setPin(D2);
  blade[2].setInitialPosition(target);
  blade[2].setMinMax(700, 2000);
  blade[2].setPin(D3);
  blade[3].setInitialPosition(target);
  blade[3].setMinMax(700, 2000);
  blade[3].setPin(D4);
  blade[4].setInitialPosition(target);
  blade[4].setMinMax(700, 2000);
  blade[4].setPin(D5);
  blade[5].setInitialPosition(target);
  blade[5].setMinMax(700, 2000);
  blade[5].setPin(D6);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
} //************End setup**************************


void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  } // End while

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
} //End setup_wifi

void callback(char *topic, byte *payload, unsigned int length)
{
  String string;
  //   display incoming Topic
  Serial.println();
  Serial.print("callback");
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
    int pos = 0;
    int PreviousPos=pos;
//    decode payload message
  for (int i = 0; i < length; i++)
  {
    string += ((char)payload[i]);
  }
  
  //  display incoming message
  Serial.print(string);
  Serial.print(" to Int ");
//    convert position as an Integer

      pos = string.toInt();
  Serial.println(pos);
  Serial.print("topic = ");
    if (strcmp(topic, topic_wench_up) == 0)
  {
    Serial.print("Wench up ");
    digitalWrite(D14, LOW); // sets the digital pin D14 on
    delay(1200);
    digitalWrite(D14, HIGH);
  }
  if (strcmp(topic, topic_wench_down) == 0)
  {
    Serial.print("Wench down ");
    digitalWrite(D15, LOW); // sets the digital pin D9 on
    delay(1200);
    digitalWrite(D15, HIGH);
  }
  
  //  Determines which servo should be moved
      for (int n = 0; n < 6; n++)
   {
    if (strcmp(topic, topic_blade[n]) == 0)
     {
       digitalWrite(D7, LOW); // sets the digital pin D7 on for servo relay
       ArduinoOTA.handle();
       delay(10);
       Serial.print("Move Blade ");
       Serial.print(n);
       Serial.print(" to ");
       Serial.print(pos);
       target = pos;
       target = 1.0 - target;
       blade[n].goTo(pos); 
      //blade[n].write(pos); old statement 
      delay(200);
      digitalWrite(D7, HIGH); // sets the digital pin 10 off for servo relay
    }
  }  
     if (strcmp(topic, topic_blade[6]) == 0)
    {
      Serial.print("Move all blades at the sametime to ");
      Serial.println(pos);
      digitalWrite(D7, LOW); // sets the digital pin D7 on for servo relay

      for (int v = 0; v < 6; v++)
      { 
        Serial.print("Test loop");
//        ArduinoOTA.handle();
//        blade[1].goto(pos);
        blade[v].goto(target);
//        delay(200);
      }
    digitalWrite(D7, HIGH); // sets the digital pin D7 off for servo relay
    delay(20);
    SlowMotionServo::update();// update Servo pos
   
    }
} //End callback

  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client"))
    {
      Serial.println("connected");
      //      for (int i = 0; i < 8; i++) {
      client.subscribe("MBR/#");

      //      }
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} // end reconnect



//**************Void Loop**************************
void loop()
{
  ArduinoOTA.handle();
  

  if (!client.connected())
  {
    Serial.println("not connected loop");
    reconnect();
  }

  client.loop();
  delay(100);
} //End loop
