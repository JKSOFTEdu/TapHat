

#define pwmTap1     2 // should be 3 in new print
#define dirTap1     11
#define tap1Time    6000

#define pwmTap2     4
#define dirTap2     12
#define tap2Time    6000

#define lead1_Tap3  5
#define lead2_Tap3  6
#define tap3Time    6000

#define CLOSE       0
#define OPEN        1

void checkTapTimer(int tap, unsigned long timerStart) {
  int tapTime = 0;
  if (tap == 1) {
    tapTime = tap1Time;
  } else if (tap == 2) {
    tapTime = tap2Time;
  } else if (tap == 3) {
    tapTime = tap3Time;
  } else {
    return; // invalid tap number
  }
  if (millis() > timerStart + tapTime) {
    tapMoving = false;
    stopTap(tap);
  }
}

void initMotorPins() {
  pinMode(pwmTap1, OUTPUT);
  pinMode(pwmTap2, OUTPUT);
  pinMode(dirTap1, OUTPUT);
  pinMode(dirTap2, OUTPUT);
  pinMode(lead1_Tap3, OUTPUT);
  pinMode(lead2_Tap3, OUTPUT);
}

void openTap(int tap) {
  setTap(tap, OPEN);
}

void closeTap(int tap) {
  setTap(tap, CLOSE);
}

void stopTap(int tap) {
  if (tap > 0 && tap <= 3) {
    if (tap == 1) {
      analogWrite(pwmTap1, 0);
    } else if (tap == 2) {
      analogWrite(pwmTap2, 0);
    } else if (tap == 3) {
      digitalWrite(lead1_Tap3, LOW); // DON'T MAKE 1 AND 2 BOTH HIGH
      digitalWrite(lead2_Tap3, LOW); // DON'T MAKE 1 AND 2 BOTH HIG
    }
  }
}

void setTap(int tap, int set) {
  if (tap > 0 && tap <= 3) {
    if (tap == 1) {
      digitalWrite(dirTap1, set);
      analogWrite(pwmTap1, 255);
    } else if (tap == 2) {
      digitalWrite(dirTap2, set);
      analogWrite(pwmTap2, 255);
    } else if (tap == 3) {
      if (set == 0) {
        digitalWrite(lead1_Tap3, LOW); // DON'T MAKE 1 AND 2 BOTH HIGH
        digitalWrite(lead2_Tap3, HIGH);
      } else {
        digitalWrite(lead2_Tap3, LOW); // DON'T MAKE 1 AND 2 BOTH HIGH
        digitalWrite(lead1_Tap3, HIGH);
      }
    }
  }
}

