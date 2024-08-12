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

    unsigned int selectedMasterSwitch;
    unsigned int selectedSecondarySwitch;

    void activate();
    void deactivate();

    void setChannel(char* newValue);
    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setSelectedSecondarySwitch(unsigned int newValue);
    void setVolume(int newValue);    
    void setSql(unsigned int newValue);
  private:
    TftDisplay* display;

    char* channel;
    char* frequency;
    int volume;
    unsigned int sql;  

    const unsigned int numMasterSwitches;
    String masterSwitches[4];

    const unsigned int numSecondarySwitches;
    String secondarySwitches[3];
};

#endif

