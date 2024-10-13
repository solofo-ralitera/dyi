#include <Joystick.h>
// #include "PushButton.h"

#define ANALOG_SAMPLE 20

// Change device name
// https://liveelectronics.musinou.net/MIDIdeviceName.php

Joystick_ joystick (JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  128, 0, // Button Count, Hat Switch Count
  false, // X
  false, // Y
  false, //Z Axis
  false, // Rx
  false, // Ry
  false,   // Rz
  true, // rudder
  false, // throttle
  false, // Accelerator, 
  true, // brake 
  false // steering
);

void setup() {
  Serial.begin(9600);

  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  // Set full axes
  // joystick.setXAxisRange(-127, 127);
  // joystick.setYAxisRange(-127, 127);
  // joystick.setZAxisRange(-127, 127);
  // joystick.setRxAxisRange(-127, 127);
  // joystick.setRyAxisRange(-127, 127);
  // joystick.setRzAxisRange(-127, 127);
  joystick.setRudderRange(0, 1023);
  // joystick.setThrottleRange(0, 765);
  // joystick.setAcceleratorRange(0, 765);
  joystick.setBrakeRange(0, 1023);
  // joystick.setSteeringRange(-127, 127);

  joystick.begin();

  // joystick.setXAxis(0);
  // joystick.setYAxis(0);
  // joystick.setZAxis(0);
  // joystick.setRxAxis(0);
  // joystick.setRyAxis(0);
  // joystick.setRzAxis(0);
  joystick.setRudder(0);
  // joystick.setThrottle(0);
  // joystick.setAccelerator(0);
  joystick.setBrake(0);
  // joystick.setSteering(0);

  //Wait for all slaves (?)
  delay(1000);

}
void loop() {
  // CLucth is rudder left
  static long analogMeanClutch = 0;
  static long analogNumSampleClutch = 0;
  static long analogSamplesClutch = 0;
  int analogValueClutch = analogRead(A1);
  static int clutch = 0;
  // 1010 - 220
  if (analogNumSampleClutch < ANALOG_SAMPLE) {
    analogSamplesClutch += analogValueClutch;
    analogNumSampleClutch += 1;
  } else {
    clutch = min(512, max(0, map(analogSamplesClutch / ANALOG_SAMPLE, 940, 210, 0, 512)));
    analogSamplesClutch = 0;
    analogNumSampleClutch = 0;
  }

  // Accelerator is rudder right
  static long analogMeanThrottle = 0;
  static long analogNumSampleThrottle = 0;
  static long analogSamplesThrottle = 0;
  int analogValueThrottle = analogRead(A3);
  static int throttle = 0;
  // 1000 - 250
  if (analogNumSampleThrottle < ANALOG_SAMPLE) {
    analogSamplesThrottle += analogValueThrottle;
    analogNumSampleThrottle += 1;
  } else {
    throttle = min(512, max(0, map(analogSamplesThrottle / ANALOG_SAMPLE, 980, 300, 0, 512)));
    analogSamplesThrottle = 0;
    analogNumSampleThrottle = 0;
  }


  static long analogMeanBrake = 0;
  static long analogNumSampleBrake = 0;
  static long analogSamplesBrake = 0;
  int analogValueBrake = analogRead(A2);
  static int brake = 0;
  if (analogNumSampleBrake < ANALOG_SAMPLE) {
    analogSamplesBrake += analogValueBrake;
    analogNumSampleBrake += 1;
  } else {
    brake = min(1023, max(0, map(analogSamplesBrake / ANALOG_SAMPLE, 1000, 210, 0, 1023)));
    joystick.setBrake(brake);
    
    analogSamplesBrake = 0;
    analogNumSampleBrake = 0;
  }

  if (clutch > throttle) {
    // Rudder left
    joystick.setRudder(clutch);
  } else if (throttle > clutch) {
    // rudder right
    joystick.setRudder(511 + throttle);
  } else {
    joystick.setRudder(512);
  }

}
