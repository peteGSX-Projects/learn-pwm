#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>
#include "EXIODimmer.h"

/* 
  Variables
*/
static Dimmer dimmers[MAX_DIMMERS];
uint8_t dimmerCount = 0;
// static volatile int8_t Channel;
static volatile int8_t dimmer = 0;

/*
  Static functions
*/
static inline void handle_interrupts(volatile uint8_t *TCNTn, volatile uint8_t *OCRnA) {
  if (dimmer < 0) {
    *TCNTn = 0;
  // } else {
  //   if (dimmers[dimmer].isActive) {
  //     digitalWrite(dimmers[dimmer].physicalPin, LOW);
  //   }
  }
  dimmer++;
  if (dimmer < MAX_DIMMERS) {
    *OCRnA = dimmers[dimmer].onValue;
    if (dimmers[dimmer].isActive && *TCNTn <= dimmers[dimmer].onValue) {
      digitalWrite(dimmers[dimmer].physicalPin, HIGH);
    } else if (dimmers[dimmer].isActive) {
      digitalWrite(dimmers[dimmer].physicalPin, LOW);
    }
  } else {
    dimmer = -1;
  }
  // Serial.println(counter);
  // if (Channel < 0) {
  //   *TCNTn = 0;
  // } else {
  // for (uint8_t counter = 0; counter <= 255; counter ++) {
    // for (uint8_t i = 0; i < MAX_DIMMERS; i++) {
    //   if (dimmers[i].isActive) {
    //     // *OCRnA = dimmers[i].onValue;
    //     if (counter <= dimmers[i].onValue) {
    //       digitalWrite(dimmers[i].physicalPin, HIGH);
    //     } else {
    //       digitalWrite(dimmers[i].physicalPin, LOW);
    //     }
    //   }
    // }
  // }
  // if (Channel < MAX_DIMMERS) {
  //   Channel++;
  // } else {
  //   Channel = -1;
  // }
}

SIGNAL (TIMER2_COMPA_vect) {
  handle_interrupts(&TCNT2, &OCR2A);
}

// SIGNAL (TIMER2_OVF_vect) {
//   handle_interrupts(&TCNT2);
// }

static void initISR() {
  TCCR2A = 0x00;
  // TCCR2A = (1<<WGM20);  // Phase correct PWM
  TCCR2B = (1<<CS21);
  // TCCR2B = (1<<CS21) + (1<<CS22);   // Prescaler 256
  TCNT2 = 0;
  TIFR2 = (1<<OCF2A);   // Clear pending interrupts
  TIMSK2 = (1<<OCIE2A); // Interrupt when hitting OCR2A
  // OCR2A = 1;
  // TIMSK2 = (1<<TOIE2);
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
  for (uint8_t Channel = 0; Channel < MAX_DIMMERS; Channel++) {
    Serial.print(Channel);
    Serial.print(F("|"));
    Serial.print(dimmers[Channel].isActive);
    Serial.print(F("|"));
    Serial.print(dimmers[Channel].physicalPin);
    Serial.print(F("|"));
    Serial.println(dimmers[Channel].onValue);
  }
}

#endif