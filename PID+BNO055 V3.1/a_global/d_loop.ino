void loop() {
  euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  depthSensor.read();
  current_roll = euler.x();
  current_pitch = euler.y();
  current_yaw = euler.z();
  current_depth = depthSensor.depth() * 1000; // in mm
  // Serial.println(current_depth);
  // Serial.println(current_yaw);

  calculate_pid(current_roll, stable_roll, current_pitch, stable_pitch,
                current_yaw, stable_yaw, current_depth, stable_depth);

  motor_left_thrust = 1650;
  motor_right_thrust = 1650;
  motor_front_thrust = 1650;
  motor_back_thrust = 1650;

  // Final Power calculation
  esc_left_power = motor_left_thrust + pid_output_yaw;
  esc_right_power = motor_right_thrust - pid_output_yaw;
  esc_front_power = motor_front_thrust + pid_output_roll - pid_output_depth;
  esc_back_power = motor_back_thrust - pid_output_roll + pid_output_depth;

  motor_move();
  // Serial.print("PID=");
  Serial.print("g");
  Serial.println(esc_left_power);
  Serial.print("d");
  Serial.println(esc_front_power);
  if (stringComplete) {
    Serial.println(inputString);
    pidtune();
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
