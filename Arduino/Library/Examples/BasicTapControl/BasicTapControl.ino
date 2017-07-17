/*
   J.A. Korten
   JKSOFT Educational
   BasicTapControl.ino

   Example: Arduino side i2c communication
   V1.0 July 12, 2017

*/

#include <Wire.h>

int currentTap = 0;
boolean tapMoving = false; // one tap at a time
unsigned long timerStart = 0;
int nextTap = 0;
int nextTapState = 0;
boolean showDebugMsg = true; 

void setup()
{
  initLEDs();                   // See second tab (download our library)

  Wire.begin(0x10);             // Pi will see the TapHat on 0x10
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);         // start serial for output
  delay(3000);
  if (showDebugMsg) Serial.println("TapHat Communication Example");
}

void loop() {
  delay(100);
  heartBeat();
  if (tapMoving) {
    checkTapTimer(currentTap, timerStart);
  } else {
    if (nextTap > 0) {
      // set tap
      setTapInMotion(nextTap, nextTapState);
      nextTap = 0;
    }
  }
}

void receiveEvent(int howMany) {
  char bufferIn[100];
  int index = 0;

  while (Wire.available() > 0) // make sure we still can read...
  {
    char input    = Wire.read();
    if (showDebugMsg) Serial.print(input);
    bufferIn[index] = input;
    index++;

    if (input == ';' || index > 4) {
      if (index == 5) {
        char tapNum    = bufferIn[1];
        char separator = bufferIn[2];
        char tapState  = bufferIn[3];
        char terminal  = bufferIn[4];

        if (separator == ':' && terminal == ';') {

          byte tap    = tapNum - '0'; // convert '0' to 0
          byte state  = tapState - '0'; // convert '0' to 0
          if (state == 0 || state == 1) {
            // at least for now we only allow one tap changing at the time
            // ignoring other tap messages while tapMoving is true
            // we will remember one next tap change only
            if (!tapMoving) {
              setTapInMotion(tap, state);
            } else {
              rememberTap(tap, state);
            }
          }
        }
      }
      Serial.println();
      index = 0;
    }
  }
}

void rememberTap(int tap, int state) {
  nextTap = tap;
  nextTapState = state;
}

void setTapInMotion(int tap, int state) {
  if (showDebugMsg) {
    Serial.print("Setting tap ");
    Serial.print(tap);
    Serial.print(" to state ");
    Serial.println(state);
  }
  setTap(tap, state);
  currentTap = tap;
  timerStart = millis();
  tapMoving = true;
}
