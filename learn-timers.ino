#include <Arduino.h>
#include "timer_functions.h"
#include "serial_function.h"

/*
Refs:
https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
https://arbaranwal.github.io/tutorial/2017/06/23/atmega328-register-reference.html
https://wolles-elektronikkiste.de/en/timer-and-pwm-part-1-8-bit-timer0-2
PCA9685 set to 50Hz clock

Focus on timer 2 (pin 3) to start.
Step 1 - get timer 2 to 50Hz (to match PCA9685).

f * scale factor = clock / (prescalar * (1 + top))

50 * 1 = 16000000
          ------
      prescalar * 256

prescalar 1024 closest to 50Hz
*/

void setup() {
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
  setupTimers();
}

void loop() {
  processSerialInput();
  if (count == pwm) {
    flash();
    count = 0;
  }
}