#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Wi-Fi
const char* ssid = "OnePlus 11R 5G";
const char* password = "12345678";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "home/relay";

// Pins
const int relayPin = 14;  // GPIO14 corresponds to D5      
const int ledPin = LED_BUILTIN; 

WiFiClient espClient;
PubSubClient client(espClient);

// MQTT callback
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) message += (char)payload[i];
  Serial.print("Message received: ");
  Serial.println(message);

  if (message == "on") {
    digitalWrite(relayPin, LOW);  
    digitalWrite(ledPin, LOW);    
    Serial.println("Relay ON");
  } else if (message == "off") {
    digitalWrite(relayPin, HIGH); 
    digitalWrite(ledPin, HIGH);   
    Serial.println("Relay OFF");
  } else {
    Serial.println("Unknown command!");
  }
}

// MQTT reconnect
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP12FClient")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(". Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Setup
void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(relayPin, HIGH);
  digitalWrite(ledPin, HIGH);

  Serial.begin(9600);
  delay(100);

  // Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("ESP IP Address: ");
  Serial.println(WiFi.localIP());

  // MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Loop
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected! Reconnecting...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nReconnected to Wi-Fi");
  }

  if (!client.connected()) {
    Serial.println("MQTT disconnected! Reconnecting...");
    reconnect();
  }

  client.loop();

  Serial.print("Relay state: ");
  Serial.println(digitalRead(relayPin) == LOW ? "ON" : "OFF");
  delay(2000);
}
