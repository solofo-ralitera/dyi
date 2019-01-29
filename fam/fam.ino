// USB 5 AXIS Controller 
// Use with Arduino Leonardo or ProMicro.
// Install Joystick library from https://github.com/MHeironimus/ArduinoJoystickLibrary

// PWM 12V
// help: https://forum.arduino.cc/index.php?topic=92776.0 => avec circuit simple pour pwm 12v
// https://forum.allaboutcircuits.com/threads/tach-frequency-calculation.98285/ => avec correspondance rpm/hz
// https://www.youtube.com/watch?v=n7bltLKnRrs / https://github.com/daniel-centore/arduino-tone-library => ne fonctionne pas sur 1.8.7 leonardo
// Build-in function: https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/

#include <Joystick.h>

Joystick_ Joystick;

//int zAxis_ = 0; 
//int RxAxis_ = 0;                    
//int RyAxis_ = 0;  
//int RzAxis_ = 0;          
int Fam = 0;         
int tachoPin = 5;

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

  pinMode(tachoPin, OUTPUT);
}
   
void loop(){

  /**** Fam ****/
  Fam = map(analogRead(A0), 624, 480, 1023, 0);         
  Joystick.setBrake(Fam);

  // Pour 4 cylindres => Hz = RPM / 30
  tone(tachoPin, 500 / 30);
  
  delay (50);
}
