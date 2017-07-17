# Pi side i2c Test (I2C_Test_PiTapHat)

import smbus
import time
import struct

bus = smbus.SMBus(1)
address = 0x10
data = [0x30, 0x3A, 0x31, 0x3B]

def toggleLed():
    data[0] = 0x31
    bus.write_i2c_block_data(address, 0, data) 

while True:
    toggleLed()
    time.sleep(10)
