#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_PRO)
#define _useTimer2
typedef enum { _timer2, _Nbr_8timers } timer8_Sequence;
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
#define _useTimer2
#endif