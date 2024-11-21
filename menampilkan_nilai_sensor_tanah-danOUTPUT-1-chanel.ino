#define soil_moisture_pin A0
#define Led1 13
#define Led2 12
int bacasensor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(soil_moisture_pin, INPUT);
}

/*void loop() {
  Serial.println(analogRead(soil_moisture_pin));
  delay(500);} */


void loop() {
  bacasensor = analogRead(soil_moisture_pin); // Instruksi untuk membaca nilai digital sensor
  if (bacasensor < 600) {             // Instruksi untuk mengaktifkan LED Merah jika api terdeteksi
    Serial.print("Digital value: ");   // Tampilkan nilai digital sensor pada serial monitor
    Serial.println(bacasensor);
    Serial.println("Water detected");  // Menampilkan karakter pada serial monitor
    digitalWrite(Led1,HIGH);
    /* digitalWrite(Led2, HIGH);
    delay(1000);
    digitalWrite(Led2,HIGH);
    delay(1000); */

  if (bacasensor < 600) {
    Serial.println(bacasensor);
    digitalWrite(Led1, HIGH);
    delay(1000);
  }
  if (bacasensor < 600) {
    Serial.println(bacasensor);
    digitalWrite(Led2, HIGH);
    delay(1000);
  }
     
  } else {
    Serial.print("Digital value: ");     //Instruksi untuk mengaktifkan LED Hijau jika tidak ada api
    Serial.println(bacasensor);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led1, LOW);
    Serial.println("No water detected"); // Menampilkan karakter pada serial monitor
    delay(1000);
  }
}

