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
    void startScreenAndBios();
    void run();
    // 0: arc210, VHF
    // 1: UHF
    // 2: VHF FM
    // 3: ILS
    // 4: TACAN
    int getActivatedModule();
    
    void activateNextModule();
    void activatePreviousModule();

    void sendDcsCommand(const char* msg, const char* args);

    unsigned int getArc210MasterMode();
    unsigned int getArc210SecondaryMode();
    
    char* getUHF100MHz();
    unsigned int getUHFMasterMode();
    unsigned int getUHFSecondaryMode();
};

#endif

