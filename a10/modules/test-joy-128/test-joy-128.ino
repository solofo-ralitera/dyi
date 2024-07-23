#include <Joystick.h>
#include <Wire.h>

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

  //Wait for all slaves (?)
  delay(1000);

  Wire.begin();
}

void loop() {
  joystick.pressButton(40);
  delay(1000);
  joystick.releaseButton(40);
}
