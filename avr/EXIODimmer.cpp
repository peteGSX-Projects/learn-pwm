#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>
#include "EXIODimmer.h"

#define DIMMER_INDEX_TO_TIMER(_dimmer_nbr) ((timer8_Sequence)(_dimmer_nbr))
#define DIMMER_INDEX_TO_CHANNEL(_dimmer_nbr) (_dimmer_nbr)
#define DIMMER_INDEX(_timer,_channel)  ((_timer*MAX_DIMMERS) + _channel)
#define DIMMER(_timer,_channel)  (dimmers[DIMMER_INDEX(_timer,_channel)])

static Dimmer dimmers[MAX_DIMMERS];
uint8_t dimmerCount = 0;

static boolean isTimerActive(timer8_Sequence timer) {
  for (uint8_t channel = 0; channel < MAX_DIMMERS; channel++) {
    if (DIMMER(timer, channel).pin.isActive == true) {
      return true;
    }
  }
  return false;
}

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