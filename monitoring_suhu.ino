// Define BLYNK_PRINT to use Serial for debugging
#define BLYNK_PRINT Serial

// Define Blynk template ID and name
#define BLYNK_TEMPLATE_ID "TMPL6smI2mWVX"
#define BLYNK_TEMPLATE_NAME "IoT"

// Include necessary libraries
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk authentication token, Wi-Fi credentials
char auth[] = "oWh2ddICZo0HkKoKB45sAHJ7hEDDV50F";
char ssid[] = "OPPO";
char pass[] = "misbah54321";

// Include the DHT library and define DHT sensor pin and type
#include "DHT.h"
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Setup function
void setup() {
  // Begin Blynk connection with authentication and Wi-Fi credentials
  Blynk.begin(auth, ssid, pass);

  // Begin DHT sensor
  dht.begin();

  // Begin Serial communication for debugging
  Serial.begin(9600); // Initialize Serial
}

// Loop function
void loop() {
  // Run Blynk tasks
  Blynk.run();

  // Call temperature and humidity function
  suhu();
}

// Temperature and humidity function
void suhu() {
  // Read temperature and humidity from DHT sensor
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Check if sensor readings are valid
  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor readings are not valid!"); // Print error message
    return;
  }

  // Send humidity and temperature values to Blynk app
  Blynk.virtualWrite(V5, h); // Send humidity to Blynk virtual pin V5
  Blynk.virtualWrite(V6, t); // Send temperature to Blynk virtual pin V6

  // Delay to avoid flooding Blynk with data
  delay(500);
}
