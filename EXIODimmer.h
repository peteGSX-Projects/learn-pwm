#ifndef EXIO_DIMMER_H
#define EXIO_DIMMER_H

#include <Arduino.h>

#if !defined(ARDUINO_ARCH_AVR)
#error "This library only works with AVR."
#endif

#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_PRO)
#define MAX_DIMMERS 16
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
#define MAX_DIMMERS 62
#endif
#define INVALID_DIMMER 255

#define MIN_ON 0
#define MAX_ON 255

typedef struct {
  uint8_t nbr;
  uint8_t isActive;
} DimmerPin;

typedef struct {
  DimmerPin pin;
  uint16_t onValue;
} Dimmer;

class EXIODimmer {
  public:
    EXIODimmer();
    uint8_t attach(uint8_t pin);
    bool attached();
    void detach();
    void write(uint16_t value);

  private:
    uint8_t dimmerIndex;
};

#endif