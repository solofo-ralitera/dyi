#ifndef Arc210_h
#define Arc210_h

#include "Arduino.h"
#include "TftDisplay.h"

class Arc210
{
  public:
    Arc210(TftDisplay*);

    const char *title;
    bool isActive;

    void begin();
    void run();

    void activate();
    void deactivate();

    void setChannel(char* newValue);
    void setFrequency(char* newValue);
    void setModulation(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setSelectedSecondarySwitch(unsigned int newValue);
    
  private:
    TftDisplay* display;

    char* channel;
    char* frequency;
    char* modulation; // AM/FM

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    String masterSwitches[4];

    unsigned int selectedSecondarySwitch;
    const unsigned int numSecondarySwitches;
    String secondarySwitches[4];
};

#endif

