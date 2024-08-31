#ifndef Tacan_h
#define Tacan_h

#include "Arduino.h"
#include "TftDisplay.h"

class Tacan
{
  public:
    Tacan(TftDisplay*);

    const char *title = "TACAN";
    bool isActive = false;

    void activate();
    void deactivate();

    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setVolume(int newValue);
    void setTest(unsigned int newValue);
    void setTone(unsigned int newValue);

  private:
    TftDisplay* display;

    char* frequency = "XXXX";
    int volume = 0;
    unsigned int tone = 0;  

    unsigned int selectedMasterSwitch = 0;
    const unsigned int numMasterSwitches = 5;
    String masterSwitches[5] = {
        "OFF",
        "REC",
        "T/R",
        "A/A Rec",
        "A/A T/R",
    };
};

#endif

