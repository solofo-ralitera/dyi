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

    char *freq100MHz;
    unsigned int selectedMasterSwitch;
    unsigned int selectedSecondarySwitch;

    void begin();
    void run();

    void activate();
    void deactivate();

    void setChannel(char* newValue);
    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    void setSelectedSecondarySwitch(unsigned int newValue);
    void set100MHz(char* newValue);
    
  private:
    TftDisplay* display;

    char* channel;
    char* frequency;

    const unsigned int numMasterSwitches;
    String masterSwitches[4];

    const unsigned int numSecondarySwitches;
    String secondarySwitches[3];
};

#endif

