#ifndef Uhf_h
#define Uhf_h

#include "Arduino.h"
#include "TftDisplay.h"

class Uhf
{
  public:
    Uhf(TftDisplay*);

    const char *title;
    bool isActive;

    void begin();
    void run();

    void activate();
    void deactivate();

    void setChannel(char* newValue);
    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setSelectedSecondarySwitch(unsigned int newValue);
    
  private:
    TftDisplay* display;

    char* channel;
    char* frequency;

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    String masterSwitches[4];

    unsigned int selectedSecondarySwitch;
    const unsigned int numSecondarySwitches;
    String secondarySwitches[3];
};

#endif

