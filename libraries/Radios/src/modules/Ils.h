#ifndef Ils_h
#define Ils_h

#include "Arduino.h"
#include "TftDisplay.h"

class Ils
{
  public:
    Ils(TftDisplay*);

    const char *title;
    bool isActive;

    void activate();
    void deactivate();

    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setVolume(int newValue);
    
  private:
    TftDisplay* display;

    char* frequency;

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    int volume;
    String masterSwitches[2];
};

#endif

