#include "Arduino.h"
#include "SlaveModule.h"
#include <Joystick.h>
#include <Wire.h>


SlaveModule::SlaveModule(
  int _i2CAddress,
  int _i2CBufferSize,
  int _numberOfFirstButton,
  int _numberOfButtons,
  int *_lasteDataI2CConfig
)
{
  i2CAddress = _i2CAddress;
  i2CBufferSize = _i2CBufferSize;
  numberOfFirstButton = _numberOfFirstButton;
  numberOfButtons = _numberOfButtons;
  lasteDataI2CConfig = _lasteDataI2CConfig;
}


// Compare le bit reçu vs le bit dans LAST_BUTTON_STATE[idx]
// Si même valeur -> raf
// Si différent -> set le statut du boutton en pressed (bitValue = 1) ou released (bitValue = 0) -> maj de la valeur du bit dans LAST_BUTTON_STATE
void SlaveModule::setBitAsJoystickStatus(Joystick_ *joystick, byte bitValue, int bitPosition) {

  int numButton = numberOfFirstButton + bitPosition;
  if (numButton >= numberOfFirstButton + numberOfButtons) {
    return;
  }
  int lastButtonsStateIndex = 0;
  if (numButton > 95) {
    // Si le numéro du botton dépasse les 96 -> passe à l'index 3
    lastButtonsStateIndex = 3;
  } else if (numButton > 63) {
    // Si le numéro du botton dépasse les 64 -> passe à l'index 2
    lastButtonsStateIndex = 2;
  } else if (numButton > 31) {
    // Si le numéro du botton dépasse les 32 -> passe à l'index 1
    lastButtonsStateIndex = 1;
  }
  // Each register has 32 bits
  int relativeBitPosition = bitPosition % 32;

  // Si le bit est le même: raf pas d'action
  if (bitValue == bitRead(lastButtonsState[lastButtonsStateIndex], relativeBitPosition)) {
    return;
  }

  if (bitValue) {
    /*
    Serial.print("Pressed ");
    Serial.print(numButton);
    Serial.println("");
    */
    joystick->pressButton(numButton);
    bitSet(lastButtonsState[lastButtonsStateIndex], relativeBitPosition);
  } else {
    /*
    Serial.print("Released ");
    Serial.print(numButton);
    Serial.println("");
    */
    joystick->releaseButton(numButton);
    bitClear(lastButtonsState[lastButtonsStateIndex], relativeBitPosition);
  }
}


// Lit le statut des boutons d'un module
// use "code" for debug
void SlaveModule::readModule(Joystick_ *joystick, int code) {
  // use to store each received bytes from i2c
  static byte wireBuffer = 0;
  Wire.requestFrom(i2CAddress, i2CBufferSize);
  if(Wire.available() == i2CBufferSize) { // Si tous les données sont bien réccupérées
    // Loop sur chaque bytes reçcus
    for (int bytesIndex = 0; bytesIndex < i2CBufferSize; bytesIndex++) {
        wireBuffer = Wire.read();
        switch (lasteDataI2CConfig[bytesIndex]) {
          case CMD_BTN:
            // Loop sur chaque bit du bytes pour avoir le statut de chaque boutton
            for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
              setBitAsJoystickStatus(joystick, bitRead(wireBuffer, bitIndex), bitIndex + (8 * bytesIndex));
            }
            break;
          case CMD_X_AXIS:
            joystick->setXAxis(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_Y_AXIS:
            joystick->setYAxis(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_Z_AXIS:
            joystick->setZAxis(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_RX_AXIS:
            joystick->setRxAxis(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_RY_AXIS:
            joystick->setRyAxis(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_RZ_AXIS:
            joystick->setRzAxis(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_RUDDER_AXIS:
            joystick->setRudder(map(wireBuffer, 0, 255, -127, 127));
            break;
          case CMD_THROTTLE_AXIS:
            joystick->setThrottle(wireBuffer);
            break;
          case CMD_ACCELERATOR_AXIS:
            joystick->setAccelerator(wireBuffer);
            break;
          case CMD_BRAKE_AXIS:
            joystick->setBrake(wireBuffer);
            break;
          case CMD_STEERING_AXIS:
            joystick->setSteering(map(wireBuffer, 0, 255, -127, 127));
            break;
            
          default:
            break;
        }
    }
  }
}
