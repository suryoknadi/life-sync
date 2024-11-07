/**
 * Intelligent Patient Health Monitoring with-IoT
 * Sensor used  : LM35, Blood Pressure (simulasi using potensiometer)
 * Database     : Firebase RTDB
 *
 * @author  Ira Adi Nata
 * @version v2024.10.07
 */

#include <WiFi.h>
#include <MQTT.h>
#include <NusabotSimpleTimer.h>

const char *ssid = "Wokwi-GUEST"; // Ganti dengan SSID WiFi Anda
const char *password = "";         // Ganti dengan password WiFi Anda

const int potPin1 = 34;            // LM35 temperature sensor
const int potPin2 = 35;            // M35 temperature sensor
const int potPin3 = 32;            // Pulse sensor
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;

WiFiClient net;
MQTTClient client;
NusabotSimpleTimer timer;

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connected to Wi-Fi
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectWiFi() {
  // Reconnect WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, attempting to reconnect...");
    connectWiFi();
  }
}

void connectMQTT() {
  Serial.print("Connecting to MQTT...");
  while (!client.connect("Hw-esp32", "lifesyncpens", "6oEYlf1rVZQq1OK7")) {
    Serial.print(".");
    delay(1000); // Delay for 1 second before retrying
  }
  Serial.println("\nConnected to MQTT broker!");
}

void publishData() {
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);

  // Print sensor values to Serial
  Serial.print("Potentiometer Value1: ");
  Serial.println(potValue1);
  Serial.print("Potentiometer Value2: ");
  Serial.println(potValue2);
  Serial.print("Potentiometer Value3: ");
  Serial.println(potValue3);

  // Publish data to MQTT broker
  client.publish("belajar/iot/suhu1", String(potValue1), false, 1);
  client.publish("belajar/iot/suhu2", String(potValue2), false, 1);
  client.publish("belajar/iot/pulse", String(potValue3), false, 1);
}

void setup() {
  Serial.begin(115200);

  // Set up pins
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(potPin3, INPUT);

  // Connect to WiFi and MQTT
  connectWiFi();
  client.begin("lifesyncpens.cloud.shiftr.io", net); // Ganti dengan alamat broker MQTT Anda
  connectMQTT();

  timer.setInterval(5000, publishData);
}

void loop() {
  // Reconnect WiFi if needed
  reconnectWiFi();

  // Ensure MQTT client stays connected
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  // Run timer
  timer.run();
}
