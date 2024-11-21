#define BuzzerPin 13 /* INI PIN A0  SENSOR--- KE A0 ESP8266 */
#define GasSensorPin A0 /* INI PIN OUTPUT AJA*/

void setup() {
  Serial.begin(115200);
  pinMode(BuzzerPin, OUTPUT);
}

void loop() {
  int gasValue = analogRead(GasSensorPin);

  int gasThreshold = 650; 

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    
    digitalWrite(BuzzerPin, HIGH);
    Serial.println("Gas detected! Buzzer is ON");
  } else {
    digitalWrite(BuzzerPin, LOW);
    Serial.println("No gas detected. Buzzer is OFF");
  }
  delay(1000); 
}