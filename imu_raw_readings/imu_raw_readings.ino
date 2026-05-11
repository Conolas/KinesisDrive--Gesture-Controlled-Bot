#include <Wire.h>

#define MPU_ADDR 0x68

void setup() {

  Serial.begin(115200);

  // SDA = 21, SCL = 22
  Wire.begin(21, 22);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("MPU6050 Raw Data");
}

void loop() {

  // Start reading from accelerometer register
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  // Request 14 bytes
  Wire.requestFrom(MPU_ADDR, 14, true);

  // Accelerometer
  int16_t ax = Wire.read() << 8 | Wire.read();
  int16_t ay = Wire.read() << 8 | Wire.read();
  int16_t az = Wire.read() << 8 | Wire.read();

  // Temperature
  int16_t temp = Wire.read() << 8 | Wire.read();

  // Gyroscope
  int16_t gx = Wire.read() << 8 | Wire.read();
  int16_t gy = Wire.read() << 8 | Wire.read();
  int16_t gz = Wire.read() << 8 | Wire.read();

  // Print Raw Data
 Serial.print("AccX:");
Serial.print(ax);
Serial.print(",");

Serial.print("AccY:");
Serial.print(ay);
Serial.print(",");

Serial.print("AccZ:");
Serial.print(az);
Serial.print(",");

Serial.print("GyroX:");
Serial.print(gx);
Serial.print(",");

Serial.print("GyroY:");
Serial.print(gy);
Serial.print(",");

Serial.print("GyroZ:");
Serial.println(gz);

  delay(100);
}