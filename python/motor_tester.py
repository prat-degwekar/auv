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
	
def move_motor( pin, width, sleep_factor ):		#moves motor on pin "pin" by pulsewidth "width" ending with a sleep call
    pi.set_servo_pulsewidth( pin, width )
    sleep( sleep_factor )
	
def pulser ( direction, percentage ):		#given percentage of speed required, returns pulse width
    cutdown = 100.00 - percentage
    if direction == "forward" :
        return ( 1750 - ( ( cutdown / 100 ) * 250 ) )
    else:
        return ( 1250 + ( ( cutdown / 100 ) * 250 ) )
		

#Access RPI GPIO
pi = pigpio.pi()

gpio.setmode(gpio.BOARD);

esc_gpio = 18
sleep_ms = 5
limit_up = 1750
limit_down = 1250
gpio.setup(esc_gpio,gpio.OUT);


stop ( esc_gpio, sleep_ms )

print('forward')

forward ( esc_gpio, limit_up, sleep_ms )	#can replace with move_motor

print('stop')

forward ( esc_gpio, pulser( "forward", 50 ), sleep_ms )

stop ( esc_gpio, sleep_ms )

print('back')

backward ( esc_gpio, pulser( "backward", 50 ), sleep_ms )

backward ( esc_gpio, limit_down, sleep_ms )

print('stop')

backward ( esc_gpio, 1400, sleep_ms )

stop ( esc_gpio, sleep_ms )

pi.stop()

gpio.cleanup()