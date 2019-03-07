# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    = mega
USER_LIB_PATH := $(realpath ../../libraries)
ARDUINO_LIBS = Adafruit_AHRS Adafruit_BNO055 Adafruit_Unified_Sensor BlueRobotics_MS5837_Library EEPROM Ethernet Firmata GSM LiquidCrystal SD SPI SensorFusion Servo SoftwareSerial Stepper TFT Wire

include /usr/share/arduino/Arduino.mk
