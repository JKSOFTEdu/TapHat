/*
 * J.A. Korten
 * JKSOFT Educational
 * I2C_Test_PiTapHat.ino
 * 
 * Example: Arduino side i2c communication
 * V1.0 July 12, 2017
 * 
 */

#include <Wire.h>

void setup()
{
  initLEDs();                   // See second tab (download our library)

  Wire.begin(0x10);             // Pi will see the TapHat on 0x10
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);         // start serial for output
  delay(1000);
  Serial.println("TapHat Communication Example");
}

void loop() {
  delay(100);
  heartBeat();
}

void receiveEvent(int howMany) {
  while (Wire.available() > 0)
  {
    byte in = Wire.read();
    if (in == 0x3A) {
      toggleAmberLed();
    }
  }
}
