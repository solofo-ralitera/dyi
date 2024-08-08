#ifndef Tacan_h
#define Tacan_h

#include "Arduino.h"
#include "TftDisplay.h"

class Tacan
{
  public:
    Tacan(TftDisplay*);

    const char *title;
    bool isActive;

    void begin();
    void run();

    void activate();
    void deactivate();

    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    
  private:
    TftDisplay* display;

    char* frequency;

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    String masterSwitches[5];
};

#endif

