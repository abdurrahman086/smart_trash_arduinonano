#include <ESP32Servo.h>

// Pin konfigurasi
const int trigPin = 12;     // Pin trig dari sensor ultrasonic dengan fungsi memancarkan sinyal ketika di beri daya/tegangan
const int echoPin = 13;    // Pin echo dari sensor ultrasonic dengan fungsi menangkap sinyal dan mengirimkan ke microconroller
const int servoPin = 15;    // Pin untuk servo

Servo servo;
long duration;
int distance;

void setup() {
  Serial.begin(9600); //Menginisialisasi komunikasi serial pada baud rate 9600 untuk debugging.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
  servo.write(0); // Posisi awal servo (tertutup)
}

void loop() {
  // Mengirimkan sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menghitung durasi waktu sinyal diterima kembali
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak (dalam cm)
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Jika jarak kurang dari atau sama dengan 10 cm, buka tutup
  if (distance <= 10) {
    servo.write(180); // Buka tutup (90 derajat)
    delay(3000);     // Tunggu 3 detik
    servo.write(0);  // Tutup kembali
  }
  delay(500);
}
