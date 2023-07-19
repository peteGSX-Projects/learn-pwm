#include "SuperPin.h"

SuperPin* SuperPin::firstPin=NULL;


// create a superpin for you to set 
// e.g. SuperPin p=new SuperPin(15);
// then set the pattern when required with p->setPattern(....)
 
SuperPin::SuperPin(byte _pinId) {
  next=firstPin;
  firstPin=this;
  pinId=_pinId;
  onCount=0;
  offCount=255;
  runningCount=255;
  pinMode(_pinId, OUTPUT);
  pinState=LOW;
  digitalWrite(pinId,pinState); 
}

// Call this to set a pattern of on/off
// setPattern(0,255) sets pin LOW
// setPattern(255,0) sets pin high
// setPattern(25,100) low frequency PWM 50%
// setPattern(1,4) high frequency PWM 50%
// and so on... 
  
void SuperPin::setPattern(byte _onCount, byte _offCount) {
  onCount=_onCount;
  offCount=_offCount;
  runningCount=0;
  pinState=LOW;  
}

void SuperPin::tick() {
  if (runningCount) {
    runningCount--;
    return;
  }
  if (pinState) {
    // pin is HIGH... switch to LOW unless locked
    if (offCount==0) {
      // pin is locked on
      runningCount=onCount;
      return; 
    }
    runningCount=offCount;
    pinState=LOW;
  }
  else {
    // pin is LOW switch to HIGH unless locked 
    if (onCount==0) {
      // pin is locked off
      runningCount=offCount;
      return; 
    }
    runningCount=onCount;
    pinState=HIGH;
  }
  digitalWrite(pinId,pinState);
  runningCount--; 
}

void SuperPin::interrupt() {
    for (SuperPin* p=firstPin; p; p=p->next) p->tick();
}

void SuperPin::start() {

  // OK... have to put some HW specific code here, taken from the CS
  // to make the timer of your choice call interrupt() at the frequency
  // of your choice.  
  // Timer1.attachInterrupt(interrupt,1); 
}
