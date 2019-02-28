/***************************************** Library Files to be used *****************************************/

#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


/*************************************** Defined constants (no memory) ***************************************/

//ESC PINS for PWM Signals

#define esc_left 32
#define esc_back 31
#define esc_front 30
#define esc_right 33


/********************************************** Global Variables *********************************************/

/************************Sensor Definitions************************/
/** BNO055 9DOF IMU Definitions **/
#define BNO055_SAMPLERATE_DELAY_MS (100)
float current_pitch, current_roll, current_yaw;
imu::Vector<3> euler; //Euler vector for BNO055 fusion data
unsigned long bno055_timer = 0;

//Stable position for forward motion test (PID Stability)
float stable_pitch, stable_yaw, stable_roll;



/************************Motor Definitions************************/

// Motor Speed Variables 

int motor_left = 0;
int motor_back = 0;
int motor_front = 0;
int motor_right = 0;

//ESC power
int esc_left_power, esc_right_power, esc_back_power, esc_front_power;

//Timers for PWM signal generation @ Port Level Access

unsigned long channel_timer_left = 0;
unsigned long channel_timer_right = 0;
unsigned long channel_timer_back = 0;
unsigned long channel_timer_front = 0;
unsigned long esc_loop_timer = 0;
unsigned long loop_timer = 0;
