#include "Arduino.h"
#include "PushButton.h"

PushButton::PushButton()
{
  lastStatus = 0;
}

PushButton::PushButton(
  byte *i2cData,
  byte *i2cDataIndex
)
{
  _i2cData = i2cData;
  _i2cDataIndex = i2cDataIndex;
  lastStatus = 0;
}

void PushButton::run(byte pinStatus) {
  if (pinStatus == 0) {
    // Serial.println("Push");
    bitSet(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
  } else {
    // Serial.println("Release");
    bitClear(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
  }
}

void PushButton::run(
  byte pinStatus,
  unsigned long *currentMillis,
  byte *i2cDataReleased
) {
  if (pinStatus == 0) {
    bitSet(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
  } else {
    // Au relachement du bouton: désactive le bouton et reactive à nouveaux pour x millis
    bitClear(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
  }
}

void PushButton::runCallBack(byte pinStatus, void (*pressCallback)(), void (*releaseCallback)()) {
  if (pinStatus == 0) {
    if (lastStatus == 0) {
      pressCallback();
      lastStatus = 1;
    }
  } else {
    if (lastStatus == 1) {
      releaseCallback();
      lastStatus = 0;
    }
  }
}

void PushButton::runCallBack(byte pinStatus, void (*pressCallback)()) {
  if (pinStatus == 0) {
    if (lastStatus == 0) {
      pressCallback();
      lastStatus = 1;
    } else {
      if (lastStatus == 1) {
        lastStatus = 0;
      }
    }
  }
}