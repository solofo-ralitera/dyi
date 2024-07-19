#include "SlaveModule.h"

// #define MODULE_LASTE 1;
#define MODULE_SAS 1;

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
  Serial.begin(9600);

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

  Wire.begin();
}

void loop() {
  #ifdef MODULE_LASTE
  static int lasteDataI2CConfig[3] = {CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule lasteAndThrottlePanel(1, 3, 0, lasteDataI2CConfig);
  lasteAndThrottlePanel.readModule(&joystick);
  #endif

  #ifdef MODULE_SAS
  static int sasDataI2CConfig[3] = {CMD_BTN, CMD_BTN, CMD_BTN};
  static SlaveModule sasAndFuel(2, 4, 24, sasDataI2CConfig);
  sasAndFuel.readModule(&joystick);
  #endif
  
}
