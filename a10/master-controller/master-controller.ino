#include "Keyboard.h"
#include "SlaveModule.h"

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

  static int radioDataI2CConfig[1] = {CMD_BTN};
  static SlaveModule radio(5, 1, 72, 3, radioDataI2CConfig);
  radio.readModule(&joystick);

  // Ufc 35 btns
  static int ufcDataI2CConfig[5] = {CMD_BTN, CMD_BTN, CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule ufc(6, 5, 75, 35, ufcDataI2CConfig);
  ufc.readModule(&joystick);
}
