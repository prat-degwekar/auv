//ESC PINS for PWM Signals

#define esc_left 32
#define esc_back 31
#define esc_front 30
#define esc_right 33

/************************Motor Definitions************************/

// Motor Speed Variables 

int motor_left = 0;
int motor_back = 0;
int motor_front = 0;
int motor_right = 0;

//ESC power
int esc_left_power, esc_right_power, esc_back_power, esc_front_power;

//Timers for PWM signal generation @ Port Level Access

unsigned long channel_timer_left, channel_timer_right, channel_timer_back, channel_timer_front, esc_loop_timer, loop_timer;
