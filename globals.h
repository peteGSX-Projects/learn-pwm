#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "EXIODimmer.h"

struct pinMap {
  uint8_t physicalPin;
  EXIODimmer dimmerObject;
};

extern bool ledState;
extern unsigned long ledPin;
extern uint16_t dutyCycle;
extern pinMap pinToDimmer[MAX_DIMMERS];

#endif