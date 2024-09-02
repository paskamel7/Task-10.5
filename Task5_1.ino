#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

float roll, pitch, yaw;
float elapsedTime, currentTime, previousTime;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read();
  accelY = Wire.read()<<8|Wire.read();
  accelZ = Wire.read()<<8|Wire.read();
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read());
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = Wire.read()<<8|Wire.read();
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;

  accAngleX = (atan(gForceY / sqrt(pow(gForceX, 2) + pow(gForceZ, 2))) * 180 / PI) - 0.58; 
  accAngleY = (atan(-1 * gForceX / sqrt(pow(gForceY, 2) + pow(gForceZ, 2))) * 180 / PI) + 1.58;
  gyroAngleX = gyroAngleX + rotX * elapsedTime; 
  gyroAngleY = gyroAngleY + rotY * elapsedTime;
  yaw = yaw + rotZ * elapsedTime;
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * gForceY;

  Serial.print("Gyro ");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print("\n");
  Serial.print(" Accel ");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.print(gForceZ);
  Serial.print("\n");
  Serial.print("roll= ");
  Serial.print(roll);
  Serial.print(" pitch=");
  Serial.print(pitch);
  Serial.print(" Yaw=");
  Serial.print(yaw);
  delay (100)}
}
