#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "username";
const char* password = "password";

// Replace with your MQTT broker details
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;


WiFiClient espClient;
PubSubClient client(espClient);

// Pin connected to relay
const int relayPin = 13; // Example pin, adjust as per your setup

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Setup MQTT broker connection
  client.setServer(mqttServer, mqttPort);
  // If MQTT broker requires authentication, set username and password
  // client.setCredentials(mqttUser, mqttPassword);

  // Callback function for receiving MQTT messages
  client.setCallback(callback);

  // Connect to MQTT broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe("esp32/relay"); // Subscribe to topic for relay control
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retry in 5 seconds");
      delay(5000);
    }
  }

  // Initialize relay pin
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Maintain MQTT connection and handle incoming messages
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  // Convert payload to a string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("Message received: " + message);

  // Control relay based on message
  if (strcmp(topic, "esp32/relay") == 0) {
    if (message == "ON") {
      digitalWrite(relayPin, HIGH); // Turn relay ON
      Serial.println("Relay turned ON");
    } else if (message == "OFF") {
      digitalWrite(relayPin, LOW); // Turn relay OFF
      Serial.println("Relay turned OFF");
    }
  }
}

void reconnect() {
  // Loop until reconnected to MQTT broker
  while (!client.connected()) {
    Serial.println("Attempting MQTT reconnection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Reconnected to MQTT broker");
      client.subscribe("esp32/relay"); // Subscribe to topic for relay control
    } else {
      Serial.print("Failed to reconnect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retry in 5 seconds");
      delay(5000);
    }
  }
}

