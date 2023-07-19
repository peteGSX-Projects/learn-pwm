#ifndef SuperPin_h
#define SuperPin_h

#include <Arduino.h>

// The variables all need to be marked volatile because they may be accessed by loop and interrupt code.
// The constructor and setpattern routines should really use nointerrupt() ... or there is a small risk of lost values. 
// It would be worth creating a static setPattern(pinid, oncount, offcount)  so the caller didn't have to remember the pointers.

class SuperPin  {
    public:
      static void start();
      SuperPin(byte _pinid);
      void setPattern(byte _onCount, byte _offCount);

    private:
      static void interrupt();
      void tick();
      static SuperPin* firstPin;
      SuperPin* next;
      byte onCount, offCount, runningCount;
      bool pinState;
      byte pinId;
};
#endif
