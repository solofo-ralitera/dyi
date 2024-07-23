#include "Arduino.h"
#include "KnobJoy.h"
#include <Encoder.h>

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
  // Serial.println(newPosition);
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

/**
 * i2cDataIndex: index du bytes pour l'axe, l'axe occupe la totalité du byte
 */
void KnobJoy::runAs8bitsAxes(int i2cDataIndex) {
  long newPosition = knob.read();
  if (newPosition <= -127) {
    newPosition = -127;
    knob.write(-127);
  } else if (newPosition >= 127) {
    newPosition = 127;
    knob.write(127);
  }
  // newPosition * -1 : to reverse the default rotation calculation (negative for right turn and positive for left turn)
  // Send bytes [0-255] instead of [-127-127] and just the first bytes of the long value
  _i2cData[i2cDataIndex] = map(newPosition, -127, 127, 0, 255) & 0b11111111;
}