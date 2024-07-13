#include "Arduino.h"
#include "AutoReleaseSwitch.h"

#define FIXED_POSITION_BUTTON_RESET_DELAY 250 // Fixed switch will be set as off after this delay (millis)

AutoReleaseSwitch::AutoReleaseSwitch(
  byte initialState,
  byte *i2cData,
  byte *i2cDataPressed,
  byte *i2cDataReleased
)
{
  _lastState = initialState;
  _i2cData = i2cData;
  _i2cDataPressed = i2cDataPressed;
  _i2cDataReleased = i2cDataReleased;
  _previousMillis = 0;
  _checkForRelease = false;
}

void AutoReleaseSwitch::run(
  byte pinStatus,
  unsigned long *currentMillis
) {
  if (pinStatus == 0 && _lastState == 1) {
    //  OFF -> ON: active un boutton,
    //    puis relâche programatiquement le boutton après FIXED_POSITION_BUTTON_RESET_DELAY millis
    bitSet(_i2cData[_i2cDataPressed[0]], _i2cDataPressed[1]);
    bitClear(_i2cData[_i2cDataReleased[0]], _i2cDataReleased[1]);
    _lastState = 0;
    _previousMillis = *currentMillis;
    _checkForRelease = true;
  }
  //  ON -> OFF: active un autre boutton
  //    puis relâche programatiquement le boutton après FIXED_POSITION_BUTTON_RESET_DELAY millis
  else if (pinStatus == 1 && _lastState == 0) {
    bitSet(_i2cData[_i2cDataReleased[0]], _i2cDataReleased[1]);
    bitClear(_i2cData[_i2cDataPressed[0]], _i2cDataPressed[1]);
    _lastState = 1;
    _previousMillis = *currentMillis;
    _checkForRelease = true;
  }
  // Relâche le dernier statut du boutton après FIXED_POSITION_BUTTON_RESET_DELAY
  // Pour éviter de maintenir le boutton appuyé
  if (_checkForRelease && (*currentMillis - _previousMillis) >= FIXED_POSITION_BUTTON_RESET_DELAY) {
    bitClear(_i2cData[_i2cDataPressed[0]], _i2cDataPressed[1]);
    bitClear(_i2cData[_i2cDataReleased[0]], _i2cDataReleased[1]);
    _checkForRelease = false;
  }
}
