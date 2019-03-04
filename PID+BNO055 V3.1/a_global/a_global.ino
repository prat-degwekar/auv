/***************************************** Library Files to be used
 * *****************************************/

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <EEPROM.h>
#include <MS5837.h>
#include <Servo.h>
#include <Wire.h>
#include <utility/imumaths.h>

#define DEBUG
#ifdef DEBUG
#define D(x) do {x} while(0)
#else
#define D(x)
#endif

// ESC PINS for PWM Signals

Servo left;
Servo right;
Servo front;
Servo back;

/********************************************** Global Variables
 * *********************************************/

/************************Sensor Definitions************************/
/** BNO055 9DOF IMU Definitions **/
#define BNO055_SAMPLERATE_DELAY_MS (100)
float current_pitch, current_roll, current_yaw;
imu::Vector<3> euler; // Euler vector for BNO055 fusion data
unsigned long bno055_timer = 0;

/** MS5837 Depth Sensor Definitions **/
MS5837 depthSensor;
float current_depth;
float stable_depth;

// Stable position for forward motion test (PID Stability)
float stable_pitch, stable_yaw, stable_roll;

/************************Motor Definitions************************/

// Motor Speed Variables

int motor_left_thrust = 0;
int motor_back_thrust = 0;
int motor_front_thrust = 0;
int motor_right_thrust = 0;

// ESC power
int esc_left_power, esc_right_power, esc_back_power, esc_front_power;
