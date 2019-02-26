import smbus                    #import SMBus module of I2C
import math
import time          #import
from math import atan


#some MPU6050 Registers and their Address
PWR_MGMT_1   = 0x6B
SMPLRT_DIV   = 0x19
CONFIG       = 0x1A
GYRO_CONFIG  = 0x1B
INT_ENABLE   = 0x38
ACCEL_XOUT_H = 0x3B
ACCEL_YOUT_H = 0x3D
ACCEL_ZOUT_H = 0x3F
GYRO_XOUT_H  = 0x43
GYRO_YOUT_H  = 0x45
GYRO_ZOUT_H  = 0x47
PastX=0
PastY=0
PastZ=0
m=0.9
n=0.1
i=1
Ax = 0
Ay = 0
Az = 0
t=time.time()




def MPU_Init():
        #write to sample rate register
        bus.write_byte_data(Device_Address, SMPLRT_DIV, 7)
        
        #Write to power management register
        bus.write_byte_data(Device_Address, PWR_MGMT_1, 1)
        
        #Write to Configuration register
        bus.write_byte_data(Device_Address, CONFIG, 0)
        
        #Write to Gyro configuration register
        bus.write_byte_data(Device_Address, GYRO_CONFIG, 24)
        
        #Write to interrupt enable register
        bus.write_byte_data(Device_Address, INT_ENABLE, 1)

def read_raw_data(addr):
        #Accelero and Gyro value are 16-bit
        high = bus.read_byte_data(Device_Address, addr)
        low = bus.read_byte_data(Device_Address, addr+1)
    
        #concatenate higher and lower value
        value = ((high << 8) | low)
        
        #to get signed value from mpu6050
        if(value > 32768):
                value = value - 65536
        return value


bus = smbus.SMBus(1)    # or bus = smbus.SMBus(0) for older version boards
Device_Address = 0x68   # MPU6050 device address

MPU_Init()

print (" Reading Data of Gyroscope and Accelerometer")

while True:
        timePrev = t;
        t = time.time();
        timeStep = (t - timePrev) / 1000; 
        if(i==1):
                for j in range(1,100):
                        #Read Accelerometer raw value
                        acc_x = read_raw_data(ACCEL_XOUT_H)
                        acc_y = read_raw_data(ACCEL_YOUT_H)
                        acc_z = read_raw_data(ACCEL_ZOUT_H)
                        #Read Gyroscope raw value
                        gyro_x = read_raw_data(GYRO_XOUT_H)
                        gyro_y = read_raw_data(GYRO_YOUT_H)
                        gyro_z = read_raw_data(GYRO_ZOUT_H)
                        #Full scale range +/- 250 degree/C as per sensitivity scale factor
                        Ax = Ax + acc_x/16384.0
                        Ay = Ay + acc_y/16384.0
                        Az = Az + acc_z/16384.0
                        time.sleep(0.01)
                Ax = Ax/100;
                Ay = Ay/100;
                Az = Az/100;
                Ax = Ax-0.02
                Ay = Ay + 0.01
                Az = Az + 0.15
                AcceX = (180/3.141592)*atan(Ax/(math.sqrt(Az*Az+Ay*Ay)))
                AcceY = (180/3.141592)*atan(Ay/(math.sqrt(Ax*Ax+Az*Az)))
                AcceZ = (180/3.141592)*atan(Az/(math.sqrt(Ay*Ay+Ax*Ax)))
                Gx = gyro_x/131.0
                Gy = gyro_y/131.0
                Gz = gyro_z/131.0
                GyroX = AcceX
                GyroY = AcceY
                GyroZ = AcceZ
                i=i+1
        
        else:
                #Read Accelerometer raw value
                acc_x = read_raw_data(ACCEL_XOUT_H)
                acc_y = read_raw_data(ACCEL_YOUT_H)
                acc_z = read_raw_data(ACCEL_ZOUT_H)
                #Read Gyroscope raw value
                gyro_x = read_raw_data(GYRO_XOUT_H)
                gyro_y = read_raw_data(GYRO_YOUT_H)
                gyro_z = read_raw_data(GYRO_ZOUT_H)
                #Full scale range +/- 250 degree/C as per sensitivity scale factor
                Ax = acc_x/16384.0
                Ay = acc_y/16384.0
                Az = acc_z/16384.0
                Ax = Ax - 0.02
                Ay = Ay + 0.01
                Az = Az + 0.15
                Gx = gyro_x/131.0
                Gy = gyro_y/131.0
                Gz = gyro_z/131.0
                time.sleep(0.01)
                
                AcceX=(180/3.141592) * atan(Ax/(math.sqrt(Az*Az+Ay*Ay)))
                AcceY=(180/3.141592) * atan(Ay/(math.sqrt(Ax*Ax+Az*Az)))
                AcceZ=(180/3.141592) * atan(Az/(math.sqrt(Ax*Ax+Ay*Ay)))
        
        
        
        
        GyroX=GyroX+Gx*timeStep
        
        
        GyroY=GyroY+Gy*timeStep
        
        
        GyroZ=GyroZ+Gz*timeStep
        
        
        
        
        
        FinalX=m*AcceX+n*GyroX
        FinalY=m*AcceY+n*GyroY
        FinalZ=m*AcceZ+n*GyroZ
        
        
        
        
        

        print ("Xang=%.2f" %FinalX,"Yang=%.2f" %FinalY,"Zang=%.2f" %FinalZ)     
        

