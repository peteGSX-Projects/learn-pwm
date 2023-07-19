#include <Arduino.h>
#include "serial_function.h"
#include "SuperPin.h"

#if defined(ARDUINO_AVR_NANO)
#define MAX_SUPERPINS 16
#elif defined(ARDUINO_AVR_MEGA2560)
#define MAX_SUPERPINS 62
#elif defined(ARDUINO_BLUEPILL_F103C8)
#define MAX_SUPERPINS 28
#endif

// Last time we updated PWM
unsigned long previousMicros = 0;
// Interval between updates/frequency ~38KHz
unsigned long microInterval = 26;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Software PWM testing"));
  Serial.println(F("Set PWM/dimming duty cycle with <pin value>"));
  Serial.println(F("Value is 0 - 1000 which maps to 0 - 255"));
}

void loop() {
  processSerialInput();
}

void processSuperPins() {

}