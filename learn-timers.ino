#include <Arduino.h>
#include "globals.h"
#include "timer_functions.h"
#include "serial_function.h"
#include "EXIODimmer.h"
#include "avr/nano_dimmers.h"

bool ledState = 0;
unsigned long ledPin = 17;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("EX-IOExpander dimmer testing"));
  Serial.println(F("Set PWM/dimming duty cycle with <pin value>"));
  Serial.println(F("Value is 0 - 1000 which maps to 0 - 255"));
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  processSerialInput();
}