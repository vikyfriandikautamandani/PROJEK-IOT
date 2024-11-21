#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6kV_IR-g2"
#define BLYNK_TEMPLATE_NAME "Projek IoT"
#define BLYNK_AUTH_TOKEN "4x-jL32vqiwhRJZL1zDuPEXQjCRgxoq6" //Isi dengan token otentikasi Blynk Anda

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define Lampu D0 // Pin Lampu menyambung dengan D0

char ssid[] = "esp8266"; // Nama WiFi Anda
char pass[] = "12345678"; // Kata sandi WiFi Anda

void setup()
{
  // Debug console
  Serial.begin(9600); // Inisialisasi Serial
  pinMode(Lampu, OUTPUT); // Atur pin Lampu sebagai OUTPUT
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Koneksi ke WiFi
}
BLYNK_WRITE(V0) {
  int value = param.asInt();  // Mendapatkan nilai dari widget tombol Blynk
  digitalWrite(Lampu, value);  // Mengendalikan LED berdasarkan nilai
  Serial.println(value);
}
void loop()
{
  Blynk.run();
}
