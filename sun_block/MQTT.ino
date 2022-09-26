#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
#include "MQTT.h"

WiFiClient espClient;
PubSubClient client(espClient);


void mqtt__setup(Callback callback) {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

bool mqtt__is_connected() {
    return client.connected();
}

void mqtt__loop() {
    client.loop();
}

void mqtt__reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("MBR/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} // end reconnect

