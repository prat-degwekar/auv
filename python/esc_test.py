import math
import os
from time import sleep
os.system('sudo pigpiod')
sleep(0.1)
import pigpio
import RPi.GPIO as gpio

#Access RPI GPIO
pi = pigpio.pi()

gpio.setmode(gpio.BOARD);

esc_gpio = 18
gpio.setup(esc_gpio,gpio.OUT);

#pi.set_servo_pulsewidth(esc_gpio,0 ) # Maximum throttle.
#sleep(2)
#pi.set_servo_pulsewidth(esc_gpio, 1000) # Minimum throttle.
#sleep(1)
#pi.set_servo_pulsewidth(esc_gpio,1250);
#sleep(1)
pi.set_servo_pulsewidth(esc_gpio,1500);
sleep(5);

print('forward')
pi.set_servo_pulsewidth(esc_gpio,1750)
sleep(5);
print('stop')
pi.set_servo_pulsewidth(esc_gpio, 1600);
sleep(5)
pi.set_servo_pulsewidth(esc_gpio,1500);
sleep(5);
print('back')
pi.set_servo_pulsewidth(esc_gpio,1400);
sleep(5)
pi.set_servo_pulsewidth(esc_gpio,1250);
sleep(5);
print('stop')
pi.set_servo_pulsewidth(esc_gpio,1400);
sleep(5)
pi.set_servo_pulsewidth(esc_gpio,1500);
sleep(5);
pi.stop()

gpio.cleanup()
