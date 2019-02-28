void loop() {
  // put your main code here, to run repeatedly:
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  Serial.println("Roll: ");
  Serial.print(euler.x());
  Serial.print(" Pitch: ");
  Serial.print(euler.y());
  Serial.print(" Yaw: ");
  Serial.print(euler.z());
  Serial.print("\n");
}
