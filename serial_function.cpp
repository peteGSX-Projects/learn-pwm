#include <Arduino.h>
#include "serial_function.h"
#include "timer_functions.h"

bool newSerialData = false;   // Flag for new serial data being received
const byte numSerialChars = 10;   // Max number of chars for serial input
char serialInputChars[numSerialChars];  // Char array for serial input
volatile uint16_t dutyCycle = 0;

void processSerialInput() {
  static bool serialInProgress = false;
  static byte serialIndex = 0;
  char startMarker = '<';
  char endMarker = '>';
  char serialChar;
  while (Serial.available() > 0 && newSerialData == false) {
    serialChar = Serial.read();
    if (serialInProgress == true) {
      if (serialChar != endMarker) {
        serialInputChars[serialIndex] = serialChar;
        serialIndex++;
        if (serialIndex >= numSerialChars) {
          serialIndex = numSerialChars - 1;
        }
      } else {
        serialInputChars[serialIndex] = '\0';
        serialInProgress = false;
        serialIndex = 0;
        newSerialData = true;
      }
    } else if (serialChar == startMarker) {
      serialInProgress = true;
    }
  }
  if (newSerialData == true) {
    newSerialData = false;
    char * strtokIndex;
    strtokIndex = strtok(serialInputChars, " ");
    unsigned long setLED = strtol(strtokIndex, NULL, 10);
    strtokIndex = strtok(NULL, " ");
    unsigned long setDutyCycle = strtol(strtokIndex, NULL, 10);
    if (setDutyCycle > 1000) {
      setDutyCycle = 1000;
    } else if (setDutyCycle < 0) {
      setDutyCycle = 0;
    }
    dutyCycle = map(setDutyCycle, 0, 1000, 0, 255);
    dimLED(setLED, dutyCycle);
  }
}