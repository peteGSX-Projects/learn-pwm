#include <Arduino.h>
#include "timer_functions.h"
#include "serial_function.h"

/*
Refs:
https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
https://arbaranwal.github.io/tutorial/2017/06/23/atmega328-register-reference.html
https://wolles-elektronikkiste.de/en/timer-and-pwm-part-1-8-bit-timer0-2

Use timer 2, clock speed doesn't matter, pure duty cycle based PWM signal output for LEDs only.

Maybe 10000 max = 100.00% effectively
*/

void setup() {
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
  // setupTimers();
}

void loop() {
  
}