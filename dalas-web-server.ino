#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is connected to GPIO5
#define ONE_WIRE_BUS 5
 
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);
 
// WiFi credentials
const char* ssid = "friandika";
const char* password = "12345678";
 
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
 
const int analogInPin = A0;
float adcValue = 0;
float voltage = 0;
int bat_percentage = 0;  // Declare bat_percentage globally
 
//  Web server running on port 80
ESP8266WebServer server(80);
 

void setup()
{
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.begin();
  Serial.println(" HTTP server started");
 
  server.on("/", handleRoot);
  server.on("/data", handleData); // Register the data route
  server.begin();
}
 
 
void loop()
{
  adcValue = analogRead(analogInPin);
  voltage = (adcValue * 0.00549538);
  bat_percentage = mapfloat(voltage, 3.3, 4.2, 0, 100);  // Update bat_percentage
 
  if (bat_percentage >= 100) {
    bat_percentage = 100;
  }
  if (bat_percentage <= 0) {
    bat_percentage = 0;
  }
 
  // Read and print temperatures in Celsius
  sensors.requestTemperatures();
 
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.println(" V");
 
  Serial.print("Battery Percentage = ");
  Serial.print(bat_percentage);
  Serial.println(" %");
 
 
  Serial.print("Temperature Sensor 1: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" °C");
 
  Serial.print("Temperature Sensor 2: ");
  Serial.print(sensors.getTempCByIndex(1));
  Serial.println(" °C");
  Serial.println();
  delay(10000);
 
  server.handleClient();
}
 
 
void handleRoot() 
{
  String message = "<html><head>";
  message += "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>";
  message += "<link href='https://fonts.googleapis.com/css?family=Montserrat:400,700&display=swap' rel='stylesheet'>";
  message += "<style>";
  message += "body {font-family: 'Tahoma', sans-serif; background: linear-gradient(to right, #741bd5, #ACB6E5); text-align: center; margin: 0; padding: 0;}";
  message += "h1 {color: #fff; text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2); margin-top: 50px;}";
  message += "p {font-size: 18px; color: #333;}";
  message += ".sensor {background-color: #fff; padding: 20px; margin: 20px auto; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); width: calc(100% - 40px); max-width: 300px; opacity: 0; transform: translateY(20px); transition: transform 0.3s, box-shadow 0.3s;}";
  message += ".sensor:hover {transform: translateY(0px); box-shadow: 0 5px 15px rgba(0,0,0,0.3);}";
  message += ".sensor-value {color: #444; font-size: 24px; font-weight: bold;}";
  message += ".fade-in {animation: fadeIn 2s;}";
  message += ".sensor:nth-child(2) {animation: fadeInUp 0.5s 0.3s forwards;}";
  message += ".sensor:nth-child(3) {animation: fadeInUp 0.5s 0.6s forwards;}";
  message += ".sensor:nth-child(4) {animation: fadeInUp 0.5s 0.9s forwards;}";
  message += ".sensor:nth-child(5) {animation: fadeInUp 0.5s 1.2s forwards;}";
  message += "@keyframes fadeIn {from {opacity: 0;} to {opacity: 1;}}";
  message += "@keyframes fadeInUp {from {opacity: 0; transform: translateY(20px);} to {opacity: 1; transform: translateY(0);}}";
  message += "</style>";
  message += "<script>";
  message += "function requestData() {";
  message += "fetch('/data').then(response => response.json()).then(data => {";
  message += "document.getElementById('voltage').innerHTML = data.voltage + ' V';";
  message += "document.getElementById('percentage').innerHTML = data.percentage + ' %';";
  message += "document.getElementById('temp1').innerHTML = data.temp1 + ' °C';";
  message += "document.getElementById('temp2').innerHTML = data.temp2 + ' °C';";
  message += "}).catch(error => console.error('Error fetching data:', error));"; // Add error handling
  message += "}";
  
  // Set requestData to run immediately after the page is fully loaded
  message += "document.addEventListener('DOMContentLoaded', function() { requestData(); setInterval(requestData, 2000); });"; // Refresh rate in milliseconds
  message += "</script>";
 
  message += "</head><body>";
  message += "<h1 class='fade-in'>IoT Smart Fridge</h1>";
 
  message += "<div class='sensor fade-in'><p>Battery Voltage: <span id='voltage' class='sensor-value'></span></p></div>";
  message += "<div class='sensor fade-in'><p>Battery Percentage: <span id='percentage' class='sensor-value'></span></p></div>";
  message += "<div class='sensor fade-in'><p>Fridge Temperature: <span id='temp1' class='sensor-value'></span></p></div>";
  message += "<div class='sensor fade-in'><p>Freezer Temperature: <span id='temp2' class='sensor-value'></span></p></div>";
 
  message += "</body></html>";
 
  server.send(200, "text/html", message);
}
 
 
 
void handleData() {
  sensors.requestTemperatures();
  String json = "{";
  json += "\"voltage\":" + String(voltage, 2) + ","; // Convert float to String
  json += "\"percentage\":" + String(bat_percentage) + ",";
  json += "\"temp1\":" + String(sensors.getTempCByIndex(0), 2) + ","; // Convert float to String
  json += "\"temp2\":" + String(sensors.getTempCByIndex(1), 2); // Convert float to String
  json += "}";
  server.send(200, "application/json", json);
}
 
 
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}