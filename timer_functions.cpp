#include <Arduino.h>
#include "timer_functions.h"
#include "serial_function.h"

TimerMap pinTimers[6] = {
  {3, 2},
  {5, 0},
  {6, 0},
  {9, 1},
  {10, 1},
  {11, 2},
};

volatile byte count;
const int LED_pin = 13;
bool state = LOW;

void setupTimers() {
  cli();
  TCCR2A = (1<<WGM21);  // Wave form generation mode CTC
  TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20); // Prescalar 1024
  TIMSK2 = (1<<OCIE2A);   // Interrupt when compare match with OCR2A
  OCR2A = 255;
  pinMode(LED_pin, OUTPUT);
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
  static uint8_t counter = 0;
  counter++;
  if (counter <= pwm) {
    digitalWrite(LED_pin, HIGH);
  } else {
    digitalWrite(LED_pin, LOW);
  }
}