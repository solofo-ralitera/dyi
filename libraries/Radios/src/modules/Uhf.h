#ifndef Uhf_h
#define Uhf_h

#include "Arduino.h"
#include "TftDisplay.h"

class Uhf
{
  public:
    Uhf(TftDisplay*);

    const char *title = "UHF Fm";
    bool isActive = false;

    unsigned int selectedMasterSwitch = 0;
    unsigned int selectedSecondarySwitch = 0;

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

    char* channel = "--";
    char* frequency = "XXX.XXX";
    int volume = 0;
    unsigned int sql;  

    const unsigned int numMasterSwitches = 4;
    String masterSwitches[4] = {
        "OFF",
        "MAIN",
        "BOTH",
        "ADF",
    };

    const unsigned int numSecondarySwitches = 3;
    String secondarySwitches[3] = {
        "MNL",
        "PRESET",
        "GRD",
    };
};

#endif

