#include "Arduino.h"
#include "MasterModule.h"
#include <Joystick.h>

Joystick_ Joystick (JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  128, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);

MasterModule::MasterModule()
{
  Joystick.begin();
}

// Compare le bit reçu vs le bit dans LAST_BUTTON_STATE[idx]
// Si même valeur -> raf
// Si différent -> set le statut du boutton en pressed (bitValue = 1) ou released (bitValue = 0) -> maj de la valeur du bit dans LAST_BUTTON_STATE
void MasterModule::setBitAsJoystickStatus(byte bitValue, int firstButtonNumber, uint32_t *lastButtonsState, int bitPosition) {
  int numButton = firstButtonNumber + bitPosition;
  int lastButtonsStateIndex = 0;
  if (numButton > 63) {
    // Si le numéro du botton dépasse les 64 -> passe à l'index 2
    lastButtonsStateIndex = 2;
    bitPosition = bitPosition - 64;
  } else if (numButton > 31) {
    // Si le numéro du botton dépasse les 32 -> passe à l'index 1
    lastButtonsStateIndex = 1;
    bitPosition = bitPosition - 32;
  }

  // Si le bit est le même: raf pas d'action
  if (bitValue == bitRead(lastButtonsState[lastButtonsStateIndex], bitPosition)) {
    return;
  }
  if (bitValue) {
    Joystick.pressButton(numButton);
    bitSet(lastButtonsState[lastButtonsStateIndex], bitPosition);
  } else {
    Joystick.releaseButton(numButton);
    bitClear(lastButtonsState[lastButtonsStateIndex], bitPosition);
  }
}