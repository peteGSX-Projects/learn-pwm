#include <Arduino.h>
#include "globals.h"
#include "timer_functions.h"

// uint16_t pwmCycle = 255;

void dimLED(uint8_t pin, uint8_t value) {
  for (uint8_t i = 0; i < MAX_DIMMERS; i++) {
    if (pinToDimmer[i].physicalPin == pin) {
      Serial.println(F("Is it attached?"));
      if (!pinToDimmer[i].dimmerObject.attached()) {
        Serial.println(F("No, attach it"));
        pinToDimmer[i].dimmerObject.attach(pinToDimmer[i].physicalPin);
      }
      Serial.println(F("Now we write"));
      pinToDimmer[i].dimmerObject.write(value);
    }
  }
}

// void setupTimer() {
//   cli();
//   TCCR2A = 0x00;        // Clear modes
//   TCCR2B = 0x00;
//   TCCR2A = (1<<WGM20);  // Phase correct PWM
//   TCCR2B = (1<<CS21) + (1<<CS22);   // Prescaler 256
//   TIMSK2 = (1<<OCIE2A); // Interrupt when hitting OCR2A
//   TCNT2 = 0;            // Clear counter
//   OCR2A = 0;            // Set OCRA to 0 to start
//   sei();
// }

// ISR(TIMER2_COMPA_vect) {
//   handleInterrupts(&TCNT2, &OCR2A);
// }

// void handleInterrupts(volatile uint8_t *TCNTn, volatile uint8_t *OCRnA) {
//   if (*TCNTn <= *OCRnA) {
//     digitalWrite(ledPin, HIGH);
//   } else {
//     digitalWrite(ledPin, LOW);
//   }
// }