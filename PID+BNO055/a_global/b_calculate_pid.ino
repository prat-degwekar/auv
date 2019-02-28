void calculate_pid(float current_roll, float stable_roll, float current_pitch, float stable_pitch, float current_yaw, float stable_z) {

  /*********************************************************Roll calculations********************************************************/
  pid_error_temp = current_roll - stable_roll;
  pid_i_mem_roll = pid_i_mem_roll + pid_i_gain_roll * pid_error_temp;

  //Integral Windup Limiter
  if (pid_i_mem_roll > pid_max_roll)
  {
    pid_i_mem_roll = pid_max_roll;
  }
  else if (pid_i_mem_roll < pid_max_roll * -1)
  {
    pid_i_mem_roll = pid_max_roll * -1;
  }

  pid_output_roll = pid_p_gain_roll * pid_error_temp + pid_i_mem_roll + pid_d_gain_roll * (pid_error_temp - pid_last_error_roll);

  //PID Output (windup Limiter)

  if (pid_output_roll > pid_max_roll)
  {
    pid_output_roll = pid_max_roll;
  }
  else if (pid_output_roll < pid_max_roll * -1)
  {
    pid_output_roll = pid_max_roll * -1;
  }
  //Update new error to memory
  pid_last_error_roll = pid_error_temp;


  /********************************************************Pitch calculations********************************************************/
  pid_error_temp = current_pitch - stable_pitch;
  pid_i_mem_pitch = pid_i_mem_pitch + pid_i_gain_pitch * pid_error_temp;

  //Integral Windup Limiter
  if (pid_i_mem_pitch > pid_max_pitch)
  {
    pid_i_mem_pitch = pid_max_pitch;
  }
  else if (pid_i_mem_pitch < pid_max_pitch * -1)
  {
    pid_i_mem_pitch = pid_max_pitch * -1;
  }

  pid_output_pitch = pid_p_gain_pitch * pid_error_temp + pid_i_mem_pitch + pid_d_gain_pitch * (pid_error_temp - pid_last_error_pitch);

  //PID Output (windup Limiter)

  if (pid_output_pitch > pid_max_pitch)
  {
    pid_output_pitch = pid_max_pitch;
  }
  else if (pid_output_pitch < pid_max_pitch * -1)
  {
    pid_output_pitch = pid_max_pitch * -1;
  }
  //Update new error to memory
  pid_last_error_pitch = pid_error_temp;


  /*********************************************************Yaw calculations*********************************************************/
  pid_error_temp = current_yaw - stable_yaw; //error
  pid_i_mem_yaw = pid_i_mem_yaw + pid_i_gain_yaw * pid_error_temp; //integral(Ki*error)

  //Integral Windup Limiter
  if (pid_i_mem_yaw > pid_max_yaw)
  {
    pid_i_mem_yaw = pid_max_yaw;
  }
  else if (pid_i_mem_yaw < pid_max_yaw * -1)
  {
    pid_i_mem_yaw = pid_max_yaw * -1;
  }

  //PID OUTPUT = Kp*error + sum(Ki*error) + Kd(difference between errors) 
  pid_output_yaw = pid_p_gain_yaw * pid_error_temp + pid_i_mem_yaw + pid_d_gain_yaw * (pid_error_temp - pid_last_error_yaw);

  //PID Output (windup Limiter)

  if (pid_output_yaw > pid_max_yaw)
  {
    pid_output_yaw = pid_max_yaw;
  }
  else if (pid_output_yaw < pid_max_yaw * -1)
  {
    pid_output_yaw = pid_max_yaw * -1;
  }
  //Update new error to memory
  pid_last_error_yaw = pid_error_temp;
}
