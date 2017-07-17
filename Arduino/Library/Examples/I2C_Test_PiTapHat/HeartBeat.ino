const int ledPin =  LED_BUILTIN;// the number of the LED pin
const int amberPin =  14;// the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
int amberLedState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 50;

void initLEDs() {
  pinMode(ledPin, OUTPUT);
  pinMode(amberPin, OUTPUT);
  digitalWrite(amberPin, HIGH);
}

void heartBeat() {
  unsigned long currentMillis = millis();
  digitalWrite(amberPin, amberLedState);

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      if (currentMillis - previousMillis >= interval * 20) {
        ledState = HIGH;
        previousMillis = currentMillis;
      }
    } else {
      previousMillis = currentMillis;
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

}

void toggleAmberLed() {
  amberLedState = !amberLedState;
}

