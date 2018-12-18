import math
import os
from time import sleep
os.system('sudo pigpiod')
sleep(0.1)
import pigpio
import RPi.GPIO as gpio

def forward( pin, speed, sleep_factor ):
	# Decide a required step factor of speed or whether to send pulse width itself and change accordingly
    pi.set_servo_pulsewidth( pin, speed )
    sleep( sleep_factor )

def backward( pin, speed, sleep_factor ):
    pi.set_servo_pulsewidth( pin, speed )
    sleep( sleep_factor )

def stop( pin, sleep_factor ):
    pi.set_servo_pulsewidth( pin, 1500 )
    sleep( sleep_factor )
	

#Access RPI GPIO
pi = pigpio.pi()

gpio.setmode(gpio.BOARD);

esc_gpio = 18
sleep_ms = 5
gpio.setup(esc_gpio,gpio.OUT);

'''
#pi.set_servo_pulsewidth(esc_gpio,0 ) # Maximum throttle.
#sleep(2)
#pi.set_servo_pulsewidth(esc_gpio, 1000) # Minimum throttle.
#sleep(1)
#pi.set_servo_pulsewidth(esc_gpio,1250);
#sleep(1)
'''

#pi.set_servo_pulsewidth(esc_gpio,1500);
#sleep(5);

# Decide a required step factor of speed or whether to send pulse width itself and change accordingly

stop ( esc_gpio, sleep_ms )

print('forward')
#pi.set_servo_pulsewidth(esc_gpio,1750)
#sleep(5);
forward ( esc_gpio, 1750, sleep_ms )

print('stop')
#pi.set_servo_pulsewidth(esc_gpio, 1600);
#sleep(5)

forward ( esc_gpio, 1600, sleep_ms )

#pi.set_servo_pulsewidth(esc_gpio,1500);
#sleep(5);

stop ( esc_gpio, sleep_ms )

print('back')

#pi.set_servo_pulsewidth(esc_gpio,1400);
#sleep(5)

backward ( esc_gpio, 1400, sleep_ms )

#pi.set_servo_pulsewidth(esc_gpio,1250);
#sleep(5);

backward ( esc_gpio, 1250, sleep_ms )

print('stop')

#pi.set_servo_pulsewidth(esc_gpio,1400);
#sleep(5)

backward ( esc_gpio, 1400, sleep_ms )

#pi.set_servo_pulsewidth(esc_gpio,1500);
#sleep(5);

stop ( esc_gpio, sleep_ms )

pi.stop()

gpio.cleanup()