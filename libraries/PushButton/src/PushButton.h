/*
Gestion des bouttons poussoirs,
L'appuie du boutton maintient le joystick appuyé jusqu'au relachement du bouton
*/
#ifndef PushButton_h
#define PushButton_h

#include "Arduino.h"

#define PUSHBUTTON_DEBOUNCE_DELAY 200
#define ANALOG_SAMPLE 15

class PushButton
{
  public:
    PushButton();
    
    PushButton(
      byte *i2cData,
      byte *i2cDataIndex
    );

    static void getPBCode(int analogValue, int *numSample, int samples[], int *analogMean, int pullUpLow = 30, int pullUpHigh = 35);

    void run(
        byte pinStatus // Status of the switch pin (0 = pressed, 1 = released)
    );

    void runToggle(
        byte pinStatus,
        unsigned long *currentMillis
    );

    void run(
        byte pinStatus, // Status of the switch pin (0 = pressed, 1 = released)
        unsigned long *currentMillis,
        byte *i2cDataReleased
    );
    
    void runCallBack(
      byte pinStatus, // Status of the switch pin (0 = pressed, 1 = released)
      void (*pressCallback)(),
      void (*releaseCallback)()
    );

    void runCallBack(
      byte pinStatus, // Status of the switch pin (0 = pressed, 1 = released)
      void (*pressCallback)()
    );
  private:
    byte *_i2cData;
    byte *_i2cDataIndex;
    int lastStatus = 0;
    unsigned long previousMillis = 0;
    bool checkForRelease = false;
};

#endif

