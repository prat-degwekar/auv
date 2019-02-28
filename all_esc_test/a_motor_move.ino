void motor_move(int thrust)
{
  while (micros() - loop_timer < 4000); //Sends ESC readings every 4000us (250Hz Refresh Rate)

  loop_timer = micros();

  //Switch ON all 4 pins
  PORTH |= B01111000;
  
  esc_left_power = constrain(thrust,1000,2000);
  esc_right_power = constrain(thrust,1000,2000);
  esc_front_power = constrain(thrust,1000,2000);
  esc_back_power = constrain(thrust,1000,2000);


  channel_timer_left = esc_left_power + loop_timer;
  channel_timer_right = esc_right_power + loop_timer;
  channel_timer_back = esc_back_power + loop_timer;
  channel_timer_front = esc_front_power + loop_timer;
  //Serial.print(channel_timer_left);

  while (PORTH >= 8) //Waits till all 4 pins in OFF State
  {
    esc_loop_timer = micros();
    if (channel_timer_left <= esc_loop_timer) PORTH &= B11101111;
    if (channel_timer_right <= esc_loop_timer) PORTH &= B11110111;
    if (channel_timer_front <= esc_loop_timer) PORTH &= B11011111;
    if (channel_timer_back <= esc_loop_timer) PORTH &= B10111111;
  }
}
