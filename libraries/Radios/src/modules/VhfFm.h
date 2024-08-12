#ifndef VhfFm_h
#define VhfFm_h

#include "Arduino.h"
#include "TftDisplay.h"

class VhfFm
{
  public:
    VhfFm(TftDisplay*);

    const char *title;
    bool isActive;

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

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    String masterSwitches[4];

    unsigned int selectedSecondarySwitch;
    const unsigned int numSecondarySwitches;
    String secondarySwitches[3];
};

#endif

