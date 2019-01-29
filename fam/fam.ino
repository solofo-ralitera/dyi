// USB 5 AXIS Controller 
// Use with Arduino Leonardo or ProMicro.
// Install Joystick library from https://github.com/MHeironimus/ArduinoJoystickLibrary

// PWM 12V
// https://arduino103.blogspot.com/2012/07/commande-moteur-avec-transitor-mosfet.html

#include <Joystick.h>

Joystick_ Joystick;

//int zAxis_ = 0; 
//int RxAxis_ = 0;                    
//int RyAxis_ = 0;  
//int RzAxis_ = 0;          
int Fam = 0;         
int tachoPin = 5;

//const bool initAutoSendState = true; 

void setup()
{
  Serial.begin(9600);
  
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
  
  Serial.println(analogRead(A1));                
  
  Fam = map(analogRead(A0), 624, 480, 1023, 0);         
  Joystick.setBrake(Fam);

  analogWrite(tachoPin, analogRead(A1) / 4);
  
  delay (50);
}
