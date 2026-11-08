#include <Wire.h>
#include <MPU6050.h>
#include <ESP32Servo.h>

Servo myservo;
MPU6050 mpu;

const int Servo_1 = 17;
const int Servo_2 = 16;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  myservo1.attach(Servo_1);
  myservo2.attach(Servo_2);

  Serial.println("Initializing");
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed");
    while (1);
  }
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("accel (X Y Z): ");
  Serial.print(ax); Serial.print(" ");
  Serial.print(ay); Serial.print(" ");
  Serial.print(az); Serial.print(" ");

  Serial.print("|| gyro (X Y Z): ");
  Serial.print(gx); Serial.print(" ");
  Serial.print(gy); Serial.print(" ");
  Serial.println(gz);


  if (ax < -5000) {
    myservo1.write(0);
    myservo2.write(0);
  }
  if (ax > 5000) {
    myservo1.write(90);
    myservo2.write(90);
  }

  delay(500);
}