#include "Keyboard.h"
#include "SlaveModule.h"

// Change device name
// https://liveelectronics.musinou.net/MIDIdeviceName.php

Joystick_ joystick (JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  128, 0, // Button Count, Hat Switch Count
  true, // X
  true, // Y
  true, //Z Axis
  true, // Rx
  true, // Ry
  true,   // Rz
  true, // rudder
  true, // throttle
  true, // Accelerator, 
  true, // brake 
  true // steering
);

void setup() {
  // Serial.begin(9600);

  Keyboard.begin();

  // Set full axes
  joystick.setXAxisRange(-127, 127);
  joystick.setYAxisRange(-127, 127);
  joystick.setZAxisRange(-127, 127);
  joystick.setRxAxisRange(-127, 127);
  joystick.setRyAxisRange(-127, 127);
  joystick.setRzAxisRange(-127, 127);
  joystick.setRudderRange(-127, 127);
  joystick.setThrottleRange(0, 255);
  joystick.setAcceleratorRange(0, 255);
  joystick.setBrakeRange(0, 255);
  joystick.setSteeringRange(-127, 127);

  joystick.begin();

  joystick.setXAxis(0);
  joystick.setYAxis(0);
  joystick.setZAxis(0);
  joystick.setRxAxis(0);
  joystick.setRyAxis(0);
  joystick.setRzAxis(0);
  joystick.setRudder(0);
  joystick.setThrottle(0);
  joystick.setAccelerator(0);
  joystick.setBrake(0);
  joystick.setSteering(0);

  //Wait for all slaves (?)
  delay(1000);

  Wire.begin();
}

void loop() {
  // 15 boutons/ctrl
  static int lasteDataI2CConfig[2] = {CMD_BTN, CMD_BTN};
  static SlaveModule lasteAndThrottlePanel(1, 2, 0, 15, lasteDataI2CConfig);
  lasteAndThrottlePanel.readModule(&joystick);
  
  // 18 boutons/ctrl
  static int sasDataI2CConfig[3] = {CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule sasAndAux(2, 3, 15, 18, sasDataI2CConfig);
  sasAndAux.readModule(&joystick);

  // 18 boutons/ctrl
  static int fuelDataI2CConfig[3] = {CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule fuelAndEmerBrake(3, 3, 33, 18, fuelDataI2CConfig);
  fuelAndEmerBrake.readModule(&joystick);

  // 21 boutons/ctrl
  static int ahcpDataI2CConfig[3] = {CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule ahcpAndLandingGear(4, 3, 51, 21, ahcpDataI2CConfig);
  ahcpAndLandingGear.readModule(&joystick);

  static int radioDataI2CConfig[2] = {CMD_BTN, CMD_KEYBOARD};
  static SlaveModule radio(5, 2, 72, 3, radioDataI2CConfig);
  static bool radiocurrentRSHKeyPress = 0;
  static bool radiocurrentRARSHKeyPress = 0;
  static bool radiocurrentRCRSHKeyPress = 0;
  radio.readModule(&joystick, 0, [](byte bitValue, int bitPosition) {
    if (bitValue == 0) {
      if (bitPosition == 8) radiocurrentRSHKeyPress = 0;
      if (bitPosition == 9) radiocurrentRARSHKeyPress = 0;
      if (bitPosition == 10) radiocurrentRCRSHKeyPress = 0;
    } else {
      if (bitPosition == 8) {
        // toogle: rshift + h
        if (radiocurrentRSHKeyPress == 0) {
          Keyboard.press(KEY_RIGHT_SHIFT);
          Keyboard.press('h');
          delay(50);
          Keyboard.releaseAll();
          radiocurrentRSHKeyPress = 1;
        }
      } else if (bitPosition == 9) {
        // dec: ralt + rshift + h
        if (radiocurrentRARSHKeyPress == 0) {
          Keyboard.press(KEY_RIGHT_ALT);
          Keyboard.press(KEY_RIGHT_SHIFT);
          Keyboard.press('h');
          delay(50);
          Keyboard.releaseAll();
          radiocurrentRARSHKeyPress = 2;
        }
      } else if (bitPosition == 10) {
        // inc: rctrl + rshift + h
        if (radiocurrentRCRSHKeyPress == 0) {
          Keyboard.press(KEY_RIGHT_CTRL);
          Keyboard.press(KEY_RIGHT_SHIFT);
          Keyboard.press('h');
          delay(50);
          Keyboard.releaseAll();
          radiocurrentRCRSHKeyPress = 3;
        }
      } 
    }
  });

  // Ufc 44 btns
  static int ufcDataI2CConfig[6] = {CMD_BTN, CMD_BTN, CMD_BTN, CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule ufc(6, 6, 75, 44, ufcDataI2CConfig);
  ufc.readModule(&joystick);
}
