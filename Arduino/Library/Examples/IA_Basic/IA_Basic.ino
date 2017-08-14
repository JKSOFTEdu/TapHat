/*
  Simpel basisvoorbeeld voor Informatica Actief (2017) om kraan open en dicht te zetten.
  J.A. Korten 14 Aug 2017
*/

#define CLOSE       0
#define OPEN        1

const int  pwmTapPin     = 3; 
const int  dirTapPin     = 4;
const byte tapSpeed      = 120; // 0 .. 255

void setup() {
  pinMode(pwmTapPin, OUTPUT); // pwm pin als output
  pinMode(dirTapPin, OUTPUT); // richting pin als output
}

void loop() {
  setTap(OPEN);  // kraan open
  delay(30000);  // 30 sec wachten
  setTap(CLOSE); // kraan dicht
  delay(30000);  // 30 sec wachten
}

void setTap(int set) {
  digitalWrite(dirTapPin, set);
  analogWrite(pwmTapPin, tapSpeed);
}
