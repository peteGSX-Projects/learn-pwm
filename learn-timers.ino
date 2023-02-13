#include <Arduino.h>
#include "timer_functions.h"
#include "serial_function.h"

/*
Refs:
https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
https://arbaranwal.github.io/tutorial/2017/06/23/atmega328-register-reference.html
https://wolles-elektronikkiste.de/en/timer-and-pwm-part-1-8-bit-timer0-2
PCA9685 set to 50Hz clock

We need to enable a full 16bit PWM signal at 50Hz, so count 0 - 65535 50 times a second.

Value being sent is the "on" part of the duty cycle.
*/

void setup() {
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
  setupTimers();
}

void loop() {
  processSerialInput();
  // if (count == pwm) {
  //   flash();
  //   count = 0;
  // }
}