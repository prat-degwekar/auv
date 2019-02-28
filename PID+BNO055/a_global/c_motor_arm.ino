void motor_arm()
{
  while (micros() - loop_timer < 4000); //Sends ESC readings every 4000us (250Hz Refresh Rate)

  loop_timer = micros();

  PORTC |= B11110000;
  esc_left_power = 1500;
  esc_right_power = 1500;
  esc_front_power = 1500;
  esc_back_power = 1500;

  channel_timer_left = esc_left_power + loop_timer;
  channel_timer_right = esc_right_power + loop_timer;
  channel_timer_back = esc_back_power + loop_timer;
  channel_timer_front = esc_front_power + loop_timer;

  while (PORTC >= 16) //Waits till all pins in OFF State
  {
    esc_loop_timer = micros();
    if (channel_timer_left <= esc_loop_timer) PORTC &= B11101111;
    if (channel_timer_right <= esc_loop_timer)PORTC &= B11011111;
    if (channel_timer_front <= esc_loop_timer)PORTC &= B01111111;
    if (channel_timer_back <= esc_loop_timer) PORTC &= B10111111;
  }
}
