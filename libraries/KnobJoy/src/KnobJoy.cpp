#include "Arduino.h"
#include "KnobJoy.h"
#include <Encoder.h>

// Delay between position change (millis)
#define CHANGE_POSITION_DELAY 100
// Number of position change before triggering joystick press
#define CHANGE_POSITION_BUFFER 3


KnobJoy::KnobJoy(
  byte *i2cData,
  int pinLeft,
  int pinRight
): knob(pinLeft, pinRight)
{
  _i2cData = i2cData;
  oldPosition = 0;
  _previousMillis = 0;
  _checkForRelease = false;
}

void KnobJoy::runIndefiniteLeftRight(
  byte *i2cDataRotateLeftIndex,
  byte *i2cDataRotateRightIndex,
  unsigned long *currentMillis
) {
  long newPosition = knob.read();
  if (abs(newPosition - oldPosition) > CHANGE_POSITION_BUFFER) {
    if (_checkForRelease == false) {
      if (newPosition > oldPosition) {
        // Turn left
        bitSet(_i2cData[i2cDataRotateLeftIndex[0]], i2cDataRotateLeftIndex[1]);
        _previousMillis = *currentMillis;
        _checkForRelease = true;
      } else if (newPosition < oldPosition) {
        // Turn right
        bitSet(_i2cData[i2cDataRotateRightIndex[0]], i2cDataRotateRightIndex[1]);
        _previousMillis = *currentMillis;
        _checkForRelease = true;
      }
    }
    oldPosition = newPosition;
  }
  if (_checkForRelease && (*currentMillis - _previousMillis) >= CHANGE_POSITION_DELAY) {
    bitClear(_i2cData[i2cDataRotateLeftIndex[0]], i2cDataRotateLeftIndex[1]);
    bitClear(_i2cData[i2cDataRotateRightIndex[0]], i2cDataRotateRightIndex[1]);
    _checkForRelease = false;
  }
}