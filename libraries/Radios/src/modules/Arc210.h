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

    void activate();
    void deactivate();

    void setChannel(char* newValue);
    void setFrequency(char* newValue);
    void setModulation(char* newValue);

    unsigned int selectedMasterSwitch;
    void setSelectedMasterSwitch(unsigned int newValue);

    unsigned int selectedSecondarySwitch;
    void setSelectedSecondarySwitch(unsigned int newValue);
    
    void setSql(unsigned int newValue);

  private:
    TftDisplay* display;

    char* channel;
    char* frequency;
    char* modulation; // AM/FM

    unsigned int sql;  
    const unsigned int numMasterSwitches;
    String masterSwitches[7];

    const unsigned int numSecondarySwitches;
    String secondarySwitches[7];
};

#endif

