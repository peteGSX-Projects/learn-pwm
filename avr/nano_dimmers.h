#ifndef NANO_DIMMERS_H
#define NANO_DIMMERS_H

#include <Arduino.h>
#include "globals.h"

EXIODimmer dimmer1;
EXIODimmer dimmer2;
EXIODimmer dimmer3;
EXIODimmer dimmer4;
EXIODimmer dimmer5;
EXIODimmer dimmer6;
EXIODimmer dimmer7;
EXIODimmer dimmer8;
EXIODimmer dimmer9;
EXIODimmer dimmer10;
EXIODimmer dimmer11;
EXIODimmer dimmer12;
EXIODimmer dimmer13;
EXIODimmer dimmer14;
EXIODimmer dimmer15;
EXIODimmer dimmer16;

pinMap pinToDimmer[MAX_DIMMERS] = {
  {2,dimmer1},{3,dimmer2},{4,dimmer3},{5,dimmer4},{6,dimmer5},{7,dimmer6},{8,dimmer7},{9,dimmer8},
  {10,dimmer9},{11,dimmer10},{12,dimmer11},{13,dimmer12},{14,dimmer13},{15,dimmer14},{16,dimmer15},{17,dimmer16},
};

#endif