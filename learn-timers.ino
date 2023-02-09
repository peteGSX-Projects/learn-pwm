#include <Arduino.h>
#include "timer_functions.h"

/*
Ref: https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
Timer ref: https://arbaranwal.github.io/tutorial/2017/06/23/atmega328-register-reference.html
PCA9685 set to 50Hz clock

Looks like we need to adjust OCRnA/B to set duty cycle
*/

void setup() {
  setupTimers();
}

void loop() {

}