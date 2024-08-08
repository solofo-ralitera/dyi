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

    void begin();
    void run();

    void activate();
    void deactivate();

    void setFrequency(char* newValue);
    void setSelectedMasterSwitch(unsigned int newValue);
    
  private:
    TftDisplay* display;

    char* frequency;

    unsigned int selectedMasterSwitch;
    const unsigned int numMasterSwitches;
    String masterSwitches[2];
};

#endif

