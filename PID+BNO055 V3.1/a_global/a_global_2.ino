/** PID Gain & Limit Settings **/

// Roll

float pid_p_gain_roll = 0.00;
float pid_i_gain_roll = 0.00;
float pid_d_gain_roll = 0.00;
int pid_max_roll = 100;

// Pitch

float pid_p_gain_pitch = 2.00;
float pid_i_gain_pitch = 0.00;
float pid_d_gain_pitch = 0.01;
int pid_max_pitch = 100;

// Yaw

float pid_p_gain_yaw = 2.00;
float pid_i_gain_yaw = 0.00;
float pid_d_gain_yaw = 0.01;
int pid_max_yaw = 100;

// Depth
float pid_p_gain_depth = 3.00;
float pid_i_gain_depth = 0.00;
float pid_d_gain_depth = 0.01;
int pid_max_depth = 180;

// PID Variables
float pid_i_mem_roll = 0.0;
float pid_last_error_roll = 0.0;
float pid_output_roll;

float pid_i_mem_pitch = 0.0;
float pid_last_error_pitch = 0.0;
float pid_output_pitch;

float pid_i_mem_yaw = 0.0;
float pid_last_error_yaw = 0.0;
float pid_output_yaw;

float pid_i_mem_depth = 0.0;
float pid_last_error_depth = 0.0;
float pid_output_depth;

float pid_error_temp = 0; // Error calculation - recycled over and over for computing YPR each

String inputString = "";     // a String to hold incoming data
bool stringComplete = false; // whether the string is complete
