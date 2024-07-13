/*
Gestion des switchs à position fixe (ex switch à 2 ou trois positions)
Changement de position OFF -> ON: active un boutton,
  puis relâche le boutton (joystick) après xxx millis
Changement de position ON -> OFF: active un autre boutton
  puis relâche le boutton (joystick) après xxx millis
*/
#ifndef AutoReleaseSwitch_h
#define AutoReleaseSwitch_h

#include "Arduino.h"

class AutoReleaseSwitch
{
  public:
    AutoReleaseSwitch(
      byte initialState,
      byte *i2cData,
      byte *i2cDataPressed, // Position of the pressed button's bit in i2cData {row, index}
      byte *i2cDataReleased // Position of the released button's bit in i2cData {row, index}
    );

    void run(
        byte pinStatus, // Status of the switch pin (0 = pressed, 1 = released)
        unsigned long *currentMillis // Current time
    );
  private:
    byte *_i2cData;
    byte *_i2cDataPressed;
    byte *_i2cDataReleased;

    // will store the last state (pressed = 0 / release = 1) of the switch
    byte _lastState;
    // will store last time PIND2 was pressed
    unsigned long _previousMillis;
    bool _checkForRelease;
};

#endif

