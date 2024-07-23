/*
Gestion des switchs à position fixe (ex switch à 2 ou trois positions)
Relache automatiquement le boutton après XXX millis
*/
#ifndef AutoReleaseSwitch_h
#define AutoReleaseSwitch_h

#include "Arduino.h"

#define FIXED_POSITION_BUTTON_RESET_DELAY 250 // Fixed switch will be set as off after this delay (millis)

class AutoReleaseSwitch
{
  public:
    AutoReleaseSwitch(
      byte initialState,
      byte *i2cData,
      byte *i2cDataPressed // Position of the pressed button's bit in i2cData {row, index}
    );

    void run(
      byte pinStatus, // Status of the switch pin (0 = pressed, 1 = released)
      unsigned long *currentMillis // Current time
    );
    
    void run(
      byte pinStatus, // Status of the switch pin (0 = pressed, 1 = released)
      unsigned long *currentMillis, // Current time
      byte *i2cDataReleased // Position of the released button's bit in i2cData {row, index}
    );



  private:
    byte *_i2cData;
    byte *_i2cDataPressed;

    // will store the last state (pressed = 0 / release = 1) of the switch
    byte _lastState;
    // will store last time PIND2 was pressed
    unsigned long _previousMillis;
    bool _checkForRelease;
};

#endif

