#include <Arduino.h>
#include "timer_functions.h"

TimerMap pinTimers[6] = {
  {3, 2},
  {5, 0},
  {6, 0},
  {9, 1},
  {10, 1},
  {11, 2},
};

volatile byte count;
byte reload = 0x9C;
const int LED_pin = 13;

void setupTimers() {
  cli();
  TCCR0B = 0; 
  OCR2A = reload;
  TCCR2A = 1<<WGM21;
  TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);
  TIMSK2 = (1<<OCIE2A);
  sei();
  Serial.print("OCR2A: "); 
  Serial.println(OCR2A, HEX);
  Serial.print("TCCR2A: "); 
  Serial.println(TCCR2A, HEX);
  Serial.print("TCCR2B: ");
  Serial.println(TCCR2B, HEX);
  Serial.print("TIMSK2: "); 
  Serial.println(TIMSK2, HEX);
  Serial.println("TIMER2 Setup Finished.");
}

void flash() {
  static boolean output = HIGH;
  digitalWrite(LED_pin, output);
  output = !output;
}

ISR(TIMER2_COMPA_vect) {
  count++;
  OCR2A = reload;
}