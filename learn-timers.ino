#include <Arduino.h>
#include "globals.h"
// #include "timer_functions.h"
#include "serial_function.h"

/*
Refs:
https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
https://arbaranwal.github.io/tutorial/2017/06/23/atmega328-register-reference.html
https://wolles-elektronikkiste.de/en/timer-and-pwm-part-1-8-bit-timer0-2

Use timer 2, clock speed doesn't matter, pure duty cycle based PWM signal output for LEDs only.

Maybe 10000 max = 100.00% effectively
*/

bool ledState = 0;
unsigned long ledPin = 17;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Learning timers"));
  // setupTimer();
}

void loop() {
  processSerialInput();
}