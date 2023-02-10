#ifndef TIMER_FUNCTIONS_H
#define TIMER_FUNCTIONS_H

#include <Arduino.h>

struct TimerMap{
  uint8_t pin;
  uint8_t timer;
};

extern TimerMap pinTimers[6];
extern volatile byte count;
extern byte reload;
extern const int LED_pin;

void setupTimers();
void flash();
ISR(TIMER2_COMPA_vect);

#endif