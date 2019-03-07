void loop() {
  euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  depthSensor.read();
  current_roll = euler.z();
  current_pitch = euler.y();
  current_yaw = euler.x();
  current_depth = depthSensor.depth() * 1000 - starting_depth; //in mm
  current_depth = current_depth / 100;
  //Serial.print("Current Depth: ");
  //Serial.println(pid_output_pitch);
  //Serial.print("\tDepth.depth(): ");
  Serial.print(stable_yaw);
  Serial.print("\t");
  Serial.println(current_yaw);
  //Serial.println(starting_depth);
  //  // Serial.println(current_yaw);

  //Angle conversion (0/360 to -180/180)
  /*
    if (current_roll > 180)
    {
      current_roll = current_roll - 360;
    }
    if (current_pitch > 180)
    {
      current_pitch = current_pitch - 360;
    }
    if (current_yaw > 180)
    {
      current_yaw = current_yaw - 360;
    }
  */
  calculate_pid(current_roll, stable_roll, current_pitch, stable_pitch, current_yaw, stable_yaw, current_depth, stable_depth);

  motor_left_thrust = 1650;
  motor_right_thrust = 1650;
  motor_front_thrust = 1500;
  motor_back_thrust = 1500;
  //
  // Final Power calculation
  esc_left_power = motor_left_thrust - pid_output_yaw;
  esc_right_power = motor_right_thrust + pid_output_yaw;
  esc_front_power = motor_front_thrust + pid_output_pitch - pid_output_depth;
  esc_back_power = motor_back_thrust - pid_output_pitch - pid_output_depth;

  if (start == false)
  {
    if (abs(current_depth - stable_depth) <= 10)
    {
      start = true;
    }
    else
    {
      esc_left_power = 1500;
      esc_right_power = 1500;
    }
  }

  // Speed limiters
  if (start == true)
  {
    if (esc_left_power > 1800)
      esc_left_power = 1800;
    else if (esc_left_power < 1550)
      esc_left_power = 1550;

    if (esc_right_power > 1800)
      esc_right_power = 1800;
    else if (esc_right_power < 1550)
      esc_right_power = 1550;
  }

  if (esc_back_power > 1800)
    esc_back_power = 1800;
  else if (esc_back_power < 1300)
    esc_back_power = 1300;


  if (esc_front_power > 1800)
    esc_front_power = 1800;
  else if (esc_front_power < 1300)
    esc_front_power = 1300;

  motor_move();
  //

  //    Serial.print("PID: ");
  //    Serial.print(pid_output_yaw);
  //      Serial.print("Left Motor: ");
  //      Serial.print(esc_left_power);
  //      Serial.print("\tRight Motor: ");
  //      Serial.println(esc_right_power);
  //  Serial.print("\tError: ");
  //  Serial.println(current_pitch - stable_pitch);
  //  Serial.print("d");
  //  Serial.println(esc_front_power);

  if (stringComplete) {
    //    Serial.println(inputString);
    pidtune();
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
