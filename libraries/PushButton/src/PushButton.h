/*
Gestion des bouttons poussoirs,
L'appuie du boutton maintient le joystick appuyé jusqu'au relachement du bouton
*/
#ifndef PushButton_h
#define PushButton_h

#include "Arduino.h"

class PushButton
{
  public:
    PushButton(
      byte *i2cData,
      byte *i2cDataIndex
    );

    void run(
        byte pinStatus // Status of the switch pin (0 = pressed, 1 = released)
    );
  private:
    byte *_i2cData;
    byte *_i2cDataIndex;
};

#endif
