#define triggerPin 13
#define echoPin 12

long duration;
float jarak;

void setup()
{
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  digitalWrite(triggerPin, LOW);   //Set triggerPin low
  delayMicroseconds(2);       // delay 2 micro second

  digitalWrite(triggerPin, HIGH);  // Set triggerPin high
  delayMicroseconds(10);      // triggerPin high selama 10 micro seconds
  digitalWrite(triggerPin, LOW);   // triggerPinPin low

  duration = pulseIn(echoPin, HIGH);   //Pembacaan Echo pin dan durasi
  jarak = duration * 0.034 / 2;   ///Menghitung jarak yg sebenarnya

  Serial.print("jarak : ");
  Serial.print(jarak);
  Serial.println(" cm");

  
}