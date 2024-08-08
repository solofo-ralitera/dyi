/*
Gestion des radios Arc10, Com, UHF, ILS, Tacan
*/
#ifndef Radios_h
#define Radios_h

#include "Arduino.h"

class Radios
{
  public:
    Radios();
    void begin();
    void run();
};

#endif

