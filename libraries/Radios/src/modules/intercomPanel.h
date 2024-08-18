#ifndef IntercomPanel_h
#define IntercomPanel_h

#include "Arduino.h"
#include "TftDisplay.h"

class IntercomPanel
{
  public:
    IntercomPanel(TftDisplay*);

    const char *title = "Intercom";
    bool isActive = false;
    unsigned int selectedSecondarySwitch = 0;
    void setSelectedSecondarySwitch(unsigned int newValue);

    void activate();
    void deactivate();

    void setVolume(unsigned int newValue);
    void setHm(unsigned int newValue);

    void setIntUnmute(unsigned int newValue);
    void setIntVolume(unsigned int newValue);

    void setAimUnmute(unsigned int newValue);
    void setAimVolume(unsigned int newValue);

    void setFmUnmute(unsigned int newValue);
    void setFmVolume(unsigned int newValue);

    void setUhfUnmute(unsigned int newValue);
    void setUhfVolume(unsigned int newValue);

    void setVhfUnmute(unsigned int newValue);
    void setVhfVolume(unsigned int newValue);

  private:
    TftDisplay* display;
    unsigned int volume = 0;

    const unsigned int numSecondarySwitches = 5;
    String secondarySwitches[5] = {
        "INT",
        "FM",
        "VHF",
        "HF",
        "-",
    };

    unsigned int intVolume = 0;
    unsigned int intUnmute = 0;
    void drawInt(boolean unmuteChange = false, boolean volumChange = false);

    unsigned int aimVolume = 0;
    unsigned int aimUnmute = 0;
    void drawAim(boolean unmuteChange = false, boolean volumChange = false);

    unsigned int fmVolume = 0;
    unsigned int fmUnmute = 0;
    void drawFm(boolean unmuteChange = false, boolean volumChange = false);

    unsigned int uhfVolume = 0;
    unsigned int uhfUnmute = 0;
    void drawUhf(boolean unmuteChange = false, boolean volumChange = false);

    unsigned int vhfVolume = 0;
    unsigned int vhfUnmute = 0;
    void drawVhf(boolean unmuteChange = false, boolean volumChange = false);

};

#endif

