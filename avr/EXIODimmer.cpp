#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>
#include "EXIODimmer.h"

/* 
  Variables
*/
static Dimmer dimmers[MAX_DIMMERS];
uint8_t dimmerCount = 0;

/*
  Static functions
*/
static inline void handle_interrupts() {
  for (uint8_t dimmerIndex = 0; dimmerIndex < MAX_DIMMERS; dimmerIndex++) {
    static uint16_t counter = 0;
    counter++;
    if (counter <= dimmers[dimmerIndex].onValue) {
      digitalWrite(dimmers[dimmerIndex].pin.nbr, HIGH);
    } else {
      digitalWrite(dimmers[dimmerIndex].pin.nbr, LOW);
    }
    if (counter == 256) {
      counter = 0;
    }
  }
}

SIGNAL (TIMER2_OVF_vect) {
  handle_interrupts();
}

static void initISR() {
  TCCR2A = (0x00);  // Wave form generation
  TCCR2B = (0<<CS22) + (0<<CS21) + (1<<CS20); // Clock speed (no prescaler)
  TIMSK2 = (1<<TOIE2);  // Interrupt when TCNT2 overflows
  TIFR2 |= _BV(OCF1A);     // clear any pending interrupts
}

static boolean isTimerActive() {
  for (uint8_t channel = 0; channel < MAX_DIMMERS; channel++) {
    if (dimmers[channel].pin.isActive == true) {
      return true;
    }
  }
  return false;
}

/*
  Constructor and functions
*/

EXIODimmer::EXIODimmer() {
  if (dimmerCount < MAX_DIMMERS) {
    this->dimmerIndex = dimmerCount++;
  } else {
    this->dimmerIndex = INVALID_DIMMER;
  }
}

uint8_t EXIODimmer::attach(uint8_t pin) {
  if (this->dimmerIndex < MAX_DIMMERS) {
    pinMode(pin, OUTPUT);
    if (isTimerActive()) {
      initISR();
    }
    dimmers[this->dimmerIndex].pin.isActive = true;
  }
  return this->dimmerIndex;
}

void EXIODimmer::detach() {
  dimmers[this->dimmerIndex].pin.isActive = false;
}

void EXIODimmer::write(uint16_t value) {
  byte channel = this->dimmerIndex;
  if (channel < MAX_DIMMERS) {
    if (value < MIN_ON) {
      value = MIN_ON;
    } else if (value > MAX_ON) {
      value = MAX_ON;
    }
    cli();
    dimmers[channel].onValue = value;
  }
}

#endif