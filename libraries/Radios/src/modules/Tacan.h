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

    void activate();
    void deactivate();

    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setVolume(int newValue);
    void setTest(unsigned int newValue);
  private:
    TftDisplay* display;

    char* frequency;

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    int volume = 0;
    String masterSwitches[5];
};

#endif

