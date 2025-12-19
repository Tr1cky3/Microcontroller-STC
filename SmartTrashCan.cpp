#include <Servo.h>

// Pin definitions
#define TRIG_PIN 9
#define ECHO_PIN 10
#define IR_PIN 11
#define SERVO_PIN 12

// Constants
#define DISTANCE_THRESHOLD 10  // cm, threshold untuk mendeteksi benda
#define DELAY_TIME 3000        // ms, waktu tunggu sebelum kembali ke 90

Servo myServo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  
  myServo.write(90);  // Posisi awal servo
  Serial.begin(9600); // Untuk debugging (opsional)
}

void loop() {
  long duration, distance;
  
  // Trigger ultrasonic
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Baca echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;  // Konversi ke cm
  
  if (distance < DISTANCE_THRESHOLD) {
    // Benda terdeteksi, baca sensor IR
    int irValue = digitalRead(IR_PIN);
    
    if (irValue == HIGH) {
      // Dikembalikan (misal, objek memantulkan cahaya)
      myServo.write(180);
      Serial.println("Servo ke 180: Dikembalikan");
    } else {
      // Tidak dikembalikan
      myServo.write(0);
      Serial.println("Servo ke 0: Tidak dikembalikan");
    }
    
    delay(DELAY_TIME);  // Tunggu beberapa detik
    myServo.write(90);  // Kembali ke posisi awal
    Serial.println("Servo kembali ke 90");
  }
  
  delay(100);  // Delay loop untuk stabilitas
}