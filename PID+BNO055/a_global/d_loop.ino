void loop()
{
  euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  current_roll = euler.x();
  current_pitch = euler.y();
  current_yaw = euler.z();

  calculate_pid(current_roll, stable_roll, current_pitch, stable_pitch, current_yaw, stable_yaw);

  motor_move(1650);
}
