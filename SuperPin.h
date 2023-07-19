#ifndef SuperPin_h
#define SuperPin_h

#include <Arduino.h>

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
