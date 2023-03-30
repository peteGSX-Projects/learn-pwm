#include <Arduino.h>
#include "globals.h"
#include "timer_functions.h"

void dimLED(uint8_t pin, uint8_t value) {
  Serial.print(F("Pin|Duty: "));
  Serial.print(pin);
  Serial.print(F("|"));
  Serial.println(value);
  for (uint8_t i = 0; i < MAX_DIMMERS; i++) {
    if (pinToDimmer[i].physicalPin == pin) {
      if (!pinToDimmer[i].dimmerObject.attached()) {
        pinToDimmer[i].dimmerObject.attach(pinToDimmer[i].physicalPin);
      }
      pinToDimmer[i].dimmerObject.write(value);
    }
  }
}
