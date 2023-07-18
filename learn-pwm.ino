#include <Arduino.h>
// #include "serial_function.h"

// bool ledState = 0;
// unsigned long ledPin = 17;
// unsigned long lastUpdate = 0;

// void setup() {
//   Serial.begin(115200);
//   Serial.println(F("EX-IOExpander dimmer testing"));
//   Serial.println(F("Set PWM/dimming duty cycle with <pin value>"));
//   Serial.println(F("Value is 0 - 1000 which maps to 0 - 255"));
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, LOW);
// }

// void loop() {
//   processSerialInput();
// }

// macros for LED state
#define ON true
#define OFF false

// variables for pattern timing
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
unsigned long millisInterval = 100;

// variables for software PWM
unsigned long currentMicros = micros();
unsigned long previousMicros = 0;
// this is the frequency of the sw PWM
// frequency = 1/(2 * microInterval)
unsigned long microInterval = 26;

const byte pwmMax = 100;

// fading (for the timing)
int fadeIncrement = 1;

// typedef for properties of each sw pwm pin
typedef struct pwmPins {
  int pin;
  int pwmValue;
  bool pinState;
  int pwmTickCount;
} pwmPin;

// create the sw pwm pins
// these can be any I/O pin
// that can be set to output!
const int pinCount = 1;
const byte pins[pinCount] = {49};

pwmPin myPWMpins[pinCount];

// function to "setup" the sw pwm pin states
// modify to suit your needs
// this creates an alternating fade pattern
void setupPWMpins() {
  for (int index=0; index < pinCount; index++) {
    myPWMpins[index].pin = pins[index];

    // mix it up a little bit
    // changes the starting pwmValue for odd and even
    if (index % 2)
      myPWMpins[index].pwmValue = 25;
    else
      myPWMpins[index].pwmValue = 75;

    myPWMpins[index].pinState = ON;
    myPWMpins[index].pwmTickCount = 0;

    // unlike analogWrite(), this is necessary
    pinMode(pins[index], OUTPUT);
  }
}

void pwmFadePattern() {
  // go through each sw pwm pin, and increase
  // the pwm value. this would be like
  // calling analogWrite() on each hw pwm pin
  for (int index=0; index < pinCount; index++) {
    myPWMpins[index].pwmValue += fadeIncrement;
    if (myPWMpins[index].pwmValue > 100)
      myPWMpins[index].pwmValue = 0;
  }
}

void handlePWM() {
  currentMicros = micros();
  // check to see if we need to increment our PWM counters yet
    if (currentMicros - previousMicros >= microInterval) {
    // Increment each pin's counter
    for (int index=0; index < pinCount; index++) {
    // each pin has its own tickCounter
      myPWMpins[index].pwmTickCount++;

    // determine if we're counting on or off time
      if (myPWMpins[index].pinState == ON) {
        // see if we hit the desired on percentage
        // not as precise as 255 or 1024, but easier to do math
        if (myPWMpins[index].pwmTickCount >= myPWMpins[index].pwmValue) {
          myPWMpins[index].pinState = OFF;
        }
      } else {
        // if it isn't on, it is off
        if (myPWMpins[index].pwmTickCount >= pwmMax) {
          myPWMpins[index].pinState = ON;
          myPWMpins[index].pwmTickCount = 0;
        }
      }
      // could probably use some bitwise optimization here, digitalWrite()
      // really slows things down after 10 pins.
      digitalWrite(myPWMpins[index].pin, myPWMpins[index].pinState);
    }
    // reset the micros() tick counter.
    digitalWrite(13, !digitalRead(13));
    previousMicros = currentMicros;
  }
}

void setup() {
  setupPWMpins();
  pinMode(13, OUTPUT);
}

void loop() {
  // this is the magic for sw pwm
  // need to call this anytime you
  // have a long operation
  handlePWM();

  // check timer for fading pattern
  // this would be the same 
  // if we used analogWrite()
  currentMillis = millis();
  if (currentMillis - previousMillis >= millisInterval) {
    // moved to own funciton for clarity
    pwmFadePattern();

    // setup clock for next tick
    previousMillis = currentMillis;
  }
}

// Code from james@baldengineer.com
// email | twitter | www
// See more at: https://www.baldengineer.com/software-pwm-with-millis.html