#ifndef Ils_h
#define Ils_h

#include "Arduino.h"
#include "TftDisplay.h"

class Ils
{
  public:
    Ils(TftDisplay*);

    const char *title = "ILS";
    bool isActive = false;

    void activate();
    void deactivate();

    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setVolume(int newValue);
    void setTone(unsigned int newValue);
    
  private:
    TftDisplay* display;

    char* frequency = "XXXXXX";
    unsigned int tone = 0;  

    unsigned int selectedMasterSwitch = 0;
    const unsigned int numMasterSwitches = 2;
    int volume = 0;
    String masterSwitches[2] = {
        "OFF",
        "PWR",
    };
};

#endif

