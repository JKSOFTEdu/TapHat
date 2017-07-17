# Pi side i2c Test (I2C_Test_PiTapHat)

import smbus
import time
import struct

bus = smbus.SMBus(1)
address = 0x10

def toggleLed():
    bus.write_byte(address,0x3A)

while True:
    time.sleep(1)
    toggleLed()
