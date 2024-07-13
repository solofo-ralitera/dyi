
// USB 5 AXIS Controller 
// Use with Arduino Leonardo or ProMicro.
// Install Joystick library from https://github.com/MHeironimus/ArduinoJoystickLibrary

#include <Joystick.h>

Joystick_ Joystick;

#define FamPin A0
int FamValue;
      
// int tachoPin = 5;

void setup()
{
  // Serial.begin(9600);
  
  Joystick.begin();
  Joystick.setXAxis(0);
  Joystick.setYAxis(0);
  Joystick.setZAxis(0);
  Joystick.setRxAxis(0);
  Joystick.setRyAxis(0);
  Joystick.setRzAxis(0);
  Joystick.setRudder(0);
  Joystick.setThrottle(0);
  Joystick.setAccelerator(0);
  Joystick.setBrake(0);
  Joystick.setSteering(0);
  Joystick.setHatSwitch(0, 0);
  Joystick.setHatSwitch(1, 0);

  // pinMode(tachoPin, OUTPUT);
}
   
void loop(){

  /**** Fam ****/
  FamValue = map(analogRead(FamPin), 624, 480, 1023, 0);         
  Joystick.setThrottle(FamValue);

  // Pour 4 cylindres => Hz = RPM / 30
  // tone(tachoPin, 500 / 30);
  
  delay (50);
}
