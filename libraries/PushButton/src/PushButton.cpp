#include "Arduino.h"
#include "PushButton.h"

PushButton::PushButton()
{
}

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
    if (lastStatus == 0) {
      bitSet(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
      lastStatus = 1;
    }
  } else {
    if (lastStatus == 1) {
      bitClear(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
      lastStatus = 0;
    }
  }
}


void PushButton::runToggle(byte pinStatus, unsigned long *currentMillis) {
  if (pinStatus == 0) {
    if (lastStatus == 0) {
      lastStatus = 1;
    }
  } else {
    if (lastStatus == 1) {
      lastStatus = 0;
      checkForRelease = true;
      previousMillis = *currentMillis;
    }
  }
  if (checkForRelease && (*currentMillis - previousMillis) >= PUSHBUTTON_DEBOUNCE_DELAY) {
    if (bitRead(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]) == 0) {
      bitSet(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
    } else {
      bitClear(_i2cData[_i2cDataIndex[0]], _i2cDataIndex[1]);
    }
    checkForRelease = false;
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
    }
  } else {
    if (lastStatus == 1) {
      lastStatus = 0;
    }
  }
}

void PushButton::getPBCode(int analogValue, int *numSample, int samples[], int *analogMean, int pullUpLow = 30, int pullUpHigh = 35) {
  // No press (32 à cause du pullup)
  if (analogValue >= pullUpLow && analogValue <= pullUpHigh){
    *numSample = 0; // Reset counter
    *analogMean = 0; // Reset mean
    return;
  } 

  if (*numSample < ANALOG_SAMPLE) {
    samples[*numSample] = analogValue;
    *numSample += 1;
    return;
  }
  if (*numSample == ANALOG_SAMPLE) {
    // Calc moyenne
    long sum = 0L;
    for (int i = 0; i < ANALOG_SAMPLE; i++) {
      sum += samples[i];
    }
    *analogMean = sum / ANALOG_SAMPLE;
  }
}