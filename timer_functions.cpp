#include <Arduino.h>
#include "globals.h"
#include "timer_functions.h"

void dimLED(uint8_t pin, uint16_t value) {
  Serial.print(F("Pin|Value: "));
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

// uint16_t pwmCycle = 255;

// void setupTimer() {
//   TCCR2A = (0x00);  // Wave form generation
//   TCCR2B = (0<<CS22) + (0<<CS21) + (1<<CS20); // Clock speed (no prescaler)
//   TIMSK2 = (1<<TOIE2);  // Interrupt when TCNT2 overflows
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, LOW);
// }

// ISR(TIMER2_OVF_vect) {
//   static uint16_t counter = 0;
//   counter++;
//   if (counter <= dutyCycle) {
//     digitalWrite(ledPin, HIGH);
//   } else {
//     digitalWrite(ledPin, LOW);
//   }
//   if (counter == pwmCycle) {
//     counter = 0;
//   }
// }