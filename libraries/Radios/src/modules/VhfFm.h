#ifndef VhfFm_h
#define VhfFm_h

#include "Arduino.h"
#include "TftDisplay.h"

class VhfFm
{
  public:
    VhfFm(TftDisplay*, bool available, char *title);

    char *title = "VHF FM";
    bool isActive = false;
    bool isAvailable = true;

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

    char* channel = "xx";
    char* frequency = "XXXXXXX";
    int volume = 0;
    unsigned int sql;  

    unsigned int selectedMasterSwitch = 0;
    const unsigned int numMasterSwitches = 4;
    String masterSwitches[4] = {
        "FM",
        "AM",
        "MAN",
        "PRE",
    };

    unsigned int selectedSecondarySwitch = 0;
    const unsigned int numSecondarySwitches = 3;
    String secondarySwitches[3] = {
        "OFF",
        "TR",
        "DF",
    };
};

#endif

