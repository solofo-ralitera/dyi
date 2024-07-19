#ifndef KnobJoy_h
#define KnobJoy_h

#include "Arduino.h"
#include <Encoder.h>

class KnobJoy
{
  public:
    KnobJoy(
      byte *i2cData,
      int pinLeft,
      int pinRight
    );

    void runIndefiniteLeftRight(
      byte *i2cDataRotateLeftIndex,
      byte *i2cDataRotateRightIndex,
      unsigned long *currentMillis
    );

    /**
    * i2cDataIndex: index of the byte to update in i2c data to send
    */
    void runAs8bitsAxes(int i2cDataIndex);
    
  private:
    byte *_i2cData;
    Encoder knob;
    unsigned long _previousMillis;
    long oldPosition;
    bool _checkForRelease;
};

#endif

