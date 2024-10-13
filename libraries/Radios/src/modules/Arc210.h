#ifndef Arc210_h
#define Arc210_h

#include "Arduino.h"
#include "TftDisplay.h"

class Arc210
{
  public:
    Arc210(TftDisplay*, bool available);

    const char *title = "VHF AM/FM";
    bool isActive = false;
    bool isAvailable = true;

    void activate();
    void deactivate();

    void setChannel(char* newValue);
    void setFrequency(char* newValue);
    void setModulation(char* newValue);

    unsigned int selectedMasterSwitch = 0;
    void setSelectedMasterSwitch(unsigned int newValue);

    unsigned int selectedSecondarySwitch = 0;
    void setSelectedSecondarySwitch(unsigned int newValue);
    
    void setSql(unsigned int newValue);
    void setVolume(int newValue);    

  private:
    TftDisplay* display;

    char* channel = "--";
    char* frequency = "XXX.XXX";
    char* modulation = "--"; // AM/FM

    unsigned int sql = 0;
    int volume = 0;
    const unsigned int numMasterSwitches = 7;
    String masterSwitches[7] = {
        "OFF",
        "TR G",
        "TR",
        "ADF",
        "CHG PRST",
        "TEST",
        "ZERO",
    };

    const unsigned int numSecondarySwitches = 7;
    String secondarySwitches[7] =  {
        "ECCM MTR",
        "ECCM",
        "PRST",
        "MAN",
        "MAR",
        "243",
        "121",
    };
};

#endif

