void motor_move(int thrust)
{
  while (micros() - loop_timer < 4000); //Sends ESC readings every 4000us (250Hz Refresh Rate)

  loop_timer = micros();

  esc_left_power = thrust + pid_output_yaw;
  esc_right_power = thrust - pid_output_yaw;
  esc_front_power = thrust;
  esc_back_power = thrust;


  channel_timer_left = esc_left_power + loop_timer;
  channel_timer_right = esc_right_power + loop_timer;
  channel_timer_back = esc_back_power + loop_timer;
  channel_timer_front = esc_front_power + loop_timer;

  PORTC |= B11110000;

  while (PORTC >= 16) //Waits till all 4 pins in OFF State
  {
    esc_loop_timer = micros();
    if (channel_timer_left <= esc_loop_timer) PORTC &= B11101111;
    if (channel_timer_right <= esc_loop_timer) PORTC &= B11011111;
    if (channel_timer_front <= esc_loop_timer) PORTC &= B01111111;
    if (channel_timer_back <= esc_loop_timer) PORTC &= B10111111;
  }
}
