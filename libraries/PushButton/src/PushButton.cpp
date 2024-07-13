#include "Arduino.h"
#include "PushButton.h"


PushButton::PushButton(
  byte *i2cData,
  byte *i2cDataIndex
)
{
  _i2cData = i2cData;
  _i2cDataIndex = i2cDataIndex;
}

void PushButton::run(byte pinStatus) {
  if (pinStatus == 0) {
    bitSet(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
  } else {
    bitClear(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
  }
}
