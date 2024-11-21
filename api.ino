#define sensorPin 14     //Deklarasi sensor terhubung pada pin D5
#define ledM  12         //Deklarasi LED merah terhubung pada pin D6
#define ledH 13          //Deklarasi LED hijau terhubung pada pin D7
  
int bacasensor = 0;      // nilai awal sensor 0 
  
void setup() {
  pinMode(ledM, OUTPUT);     //Deklarasi variabel ledM sebagai Output
  pinMode(ledH, OUTPUT);     //Deklarasi variable ledH sebagai Output
  pinMode(sensorPin, INPUT); //Deklarasi variabel sensor sebagai input
  Serial.begin(9600);
}
  
void loop() {
  bacasensor = digitalRead(sensorPin); // Instruksi untuk membaca nilai digital sensor
  if (bacasensor == LOW) {             // Instruksi untuk mengaktifkan LED Merah jika api terdeteksi
    Serial.print("Digital value: ");   // Tampilkan nilai digital sensor pada serial monitor
    Serial.println(bacasensor);
    Serial.println("Flame detected");  // Menampilkan karakter pada serial monitor
    digitalWrite(ledH,LOW);
    digitalWrite(ledM, HIGH);
    delay(10);
    digitalWrite(ledM,LOW);
    delay(10);
     
  } else {
    Serial.print("Digital value: ");     //Instruksi untuk mengaktifkan LED Hijau jika tidak ada api
    Serial.println(bacasensor);
    digitalWrite(ledH, HIGH);
    digitalWrite(ledM, LOW);
    Serial.println("No flame detected"); // Menampilkan karakter pada serial monitor
    delay(1000);
  }
}