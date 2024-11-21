#define BLYNK_PRINT Serial    
#define BLYNK_TEMPLATE_ID "TMPL6smI2mWVX"
#define BLYNK_TEMPLATE_NAME "IoT"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int pump = D1;   // pin relay pada nodemcu pin D1
int sensor = A0;  // pin analog untuk membaca POT

char auth[] = "oWh2ddICZo0HkKoKB45sAHJ7hEDDV50F"; // ISI TOKEN PADA APLIKASI BLYNX ANDROID
char ssid[] = "OPPO";                             // NAMA HOTSPOT 
char pass[] = "misbah54321";                      // PASSWORD HOTSPOT

void sendSensor()
{
  double POT = analogRead(sensor);

  if (POT > 500)
  {
    Serial.println("KERING");
    digitalWrite(pump, HIGH);
  }
  else if (POT > 400 && POT < 500)
  {
    Serial.println("NORMAL");
    digitalWrite(pump, LOW);
  }
  else if (POT < 400)
  {
    Serial.println("BASAH");
    digitalWrite(pump, LOW);
  }
  Blynk.virtualWrite(V0, POT);  // Assuming you have a Gauge widget on the Blynk app linked to Virtual Pin V0
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pump, OUTPUT);
}
void loop()
{
  Blynk.run();
  sendSensor();  // Call the function to send sensor value to Blynk
  delay(100);
}
