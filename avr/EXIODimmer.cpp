#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>
#include "EXIODimmer.h"

/* 
  Variables
*/
static dimmerDefinition dimmers[MAX_DIMMERS];
uint8_t dimmerCount = 0;
static volatile uint8_t counter = 0;
static volatile int8_t dimmerChannel;

/*
  Static functions
*/
static inline void handle_interrupts(volatile uint8_t *TCNTn, volatile uint8_t* OCRnA) {
  // Serial.print(F("Interrupt for dimmer channel "));
  // Serial.println(dimmerChannel);
  if (dimmerChannel < 0) {
    *TCNTn = 0;
  } else {
    if (dimmerChannel < dimmerCount && dimmers[dimmerChannel].isActive == true) {
      digitalWrite(dimmers[dimmerChannel].physicalPin, LOW);
    }
  }
  
  dimmerChannel++;
  if (dimmerChannel < dimmerCount) {
    // Serial.print(F("Interrupt for dimmer on pin "));
    // Serial.println(dimmers[dimmerChannel].physicalPin);
    *OCRnA = *TCNTn + dimmers[dimmerChannel].onValue;
    if (dimmers[dimmerChannel].isActive == true) {
      digitalWrite(dimmers[dimmerChannel].physicalPin, HIGH);
    } else {
      *OCRnA = *TCNTn;
      dimmerChannel = -1;
    }
  }
}

SIGNAL (TIMER2_COMPA_vect) {
  handle_interrupts(&TCNT2, &OCR2A);
}

static void initISR() {
  TCCR2A = 0x00;
  TCCR2B = (1<<CS21);
  TCNT2 = 0;
  TIFR2 = (1<<OCF2A);   // Clear pending interrupts
  TIMSK2 = (1<<OCIE2A); // Interrupt when hitting OCR2A
}

static bool isTimerActive(uint8_t channel) {
  if (dimmers[channel].isActive == true) {
    return true;
  } else {
    return false;
  }
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
    if (isTimerActive(this->dimmerIndex) == false) {
      initISR();
      dimmers[this->dimmerIndex].isActive = true;
      dimmers[this->dimmerIndex].physicalPin = pin;
      pinMode(dimmers[this->dimmerIndex].physicalPin, OUTPUT);
    }
  }
  return this->dimmerIndex;
}

bool EXIODimmer::attached() {
  if (dimmers[this->dimmerIndex].isActive) {
    return true;
  } else {
    return false;
  }
}

void EXIODimmer::detach() {
  dimmers[this->dimmerIndex].isActive = false;
}

void EXIODimmer::write(uint8_t value) {
  uint8_t channel = this->dimmerIndex;
  if (channel < MAX_DIMMERS) {
    if (value < MIN_ON) {
      value = MIN_ON;
    } else if (value > MAX_ON) {
      value = MAX_ON;
    }
    uint8_t oldSREG = SREG;
    cli();
    dimmers[channel].onValue = value;
    SREG = oldSREG;
  }
}

#endif