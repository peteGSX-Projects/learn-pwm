#include <Arduino.h>
#include "globals.h"
#include "timer_functions.h"
#include "serial_function.h"

void setupTimer() {
  TCCR2A = 0x00;  // Wave form generation
  TCCR2B = (0<<CS22) + (0<<CS21) + (1<<CS20); // Clock speed (no prescaler)
  TIMSK2 = (1<<TOIE2);  // Interrupt when TCNT2 overflows
}

ISR(TIMER2_OVF_vect) {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}