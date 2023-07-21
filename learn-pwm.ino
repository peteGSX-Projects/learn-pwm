#include <Arduino.h>
#include "SuperPin.h"

#if defined(ARDUINO_AVR_NANO)
#define MAX_SUPERPINS 16
#elif defined(ARDUINO_AVR_MEGA2560)
#define MAX_SUPERPINS 62
#elif defined(ARDUINO_BLUEPILL_F103C8)
#define MAX_SUPERPINS 28
#endif

// Last time we updated PWM
unsigned long previousMicros = 0;
// Interval between updates/frequency ~38KHz
unsigned long microInterval = 26;
bool newSerialData = false;   // Flag for new serial data being received
const byte numSerialChars = 10;   // Max number of chars for serial input
char serialInputChars[numSerialChars];  // Char array for serial input

SuperPin pinD2(2);
SuperPin pinD13(13);
SuperPin pinA3(A3);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Software PWM testing"));
  Serial.println(F("Set PWM/dimming duty cycle with <pin value>"));
  Serial.println(F("Value is 0 - 255"));
  pinD2.setPattern(0, 255);
  pinD13.setPattern(0, 255);
  pinA3.setPattern(0, 255);
}

void loop() {
  processSerialInput();
  pretendTimer();
}

void pretendTimer() {
  if (micros() - previousMicros > microInterval) {
    pinD2.interrupt();
    pinD13.interrupt();
    pinA3.interrupt();
  }
}

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
    char option = strtokIndex[0];
    strtokIndex = strtok(NULL, " ");
    uint8_t on = strtoul(strtokIndex, NULL, 10);
    strtokIndex = strtok(NULL, " ");
    uint8_t off = strtoul(strtokIndex, NULL, 10);
    switch (option) {
      case '0':
        pinD2.setPattern(on, off);
        break;
      case '1':
        pinD13.setPattern(on, off);
        break;
      case '2':
        pinA3.setPattern(on, off);
        break;
      default:
        break;
    }
  }
}
