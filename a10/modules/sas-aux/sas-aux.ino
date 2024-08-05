/*******************************
Fuel System Control Panel (XXX bouttons)
  Boost Pumps Main L: switch 2 positions (ON/OFF)
  Boost Pumps Main R: switch 2 positions (ON/OFF)

  Boost Pumps Wing L: switch 2 positions (ON/OFF)
  Boost Pumps Wing R: switch 2 positions (ON/OFF)

  Wing and Fusekage External Tank Switch, EXT TKS
    WING: switch 2 position (WING/OFF)
    FUS: switch 2 position (FUS/OFF)
  
  Crossfeed: switch 2 position (ON/OFF)
  TK Gate: switch 2 position (OPEN/OFF)
  Air Refuel Process: lever 2 position;

  Fill Disable Wing L: pull/push button
  Fill Disable Wing R: pull puch button

  Fill Disable Main L: pull puch button
  Fill Disable Main R: pull puch button

  Line Check: n/a
  Sig Ampl: n/a

  RCVR LT: analog rotary (n/a ?)

SAS Panel
  Yaw SAS L: switch 2 positions (ON/OFF)
  Yaw SAS R: switch 2 positions (ON/OFF)

  Pitch SAS L: switch 2 positions (ON/OFF)
  Pitch SAS R: switch 2 positions (ON/OFF)

  Yaw trim: rotary knob
  Yaw trim reset (only in game): push button on rotary
  
  Monitor test: horizontal switch 3 position 
  T/O Trim: push button

Aux Panel
*******************************/

#include <Wire.h>
#include "PushButton.h"
#include "AutoReleaseSwitch.h"
#include "KnobJoy.h"


// Adresse I2C du module
#define I2C_ADDRESS 2
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 3
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
};

// SAS Panel
#define BTN_IDX_TO_TRIM 0
#define BTN_IDX_MONITOR_TEST_LEFT 1
#define BTN_IDX_MONITOR_TEST_RIGHT 2
#define BTN_IDX_MONITOR_TEST_OFF 3
#define BTN_IDX_YAW_TRIM_LEFT 4
#define BTN_IDX_YAW_TRIM_RIGHT 5
#define BTN_IDX_YAW_SAS_ENGAGE_LEFT 6
#define BTN_IDX_YAW_SAS_ENGAGE_RIGHT 7
#define BTN_IDX_PITCH_SAS_ENGAGE_LEFT 8
#define BTN_IDX_PITCH_SAS_ENGAGE_RIGHT 9
// Aux Panel
#define BTN_IDX_FIRE_DETECT 10
#define BTN_IDX_SIGNAL_LIGHTS_TEST 11
#define BTN_IDX_HARS_SAS_OVERRIDE 12
#define BTN_IDX_REFUEL_LTS_DIM 13
#define BTN_IDX_REFUEL_LTS_BRT 14
#define BTN_IDX_NVIS_LTS_TOP 15
#define BTN_IDX_NVIS_LTS_ALL 16
#define BTN_IDX_NVIS_LTS_OFF 17


// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[24][2] = {
  {0, 0},
  {0, 1},
  {0, 2},
  {0, 3},
  {0, 4},
  {0, 5},
  {0, 6},
  {0, 7},
  {1, 0},
  {1, 1},
  {1, 2},
  {1, 3},
  {1, 4},
  {1, 5},
  {1, 6},
  {1, 7},
  {2, 0},
  {2, 1},
  {2, 2},
  {2, 3},
  {2, 4},
  {2, 5},
  {2, 6},
  {2, 7},
};

void requestEvent()
{
  Wire.write(I2C_DATA, BUFFER_SIZE);
}

void setup() {
  // Serial.begin(9600);
  
  // Force les digitals pins des ports B/C/D en configuration entrée (0), 
  // !!! pin 0 et 1 non disponible quand Serial est activé
  // !!! pin A4 et A5 pour l'I2C
  // !!! Enlever le build in led pour pin 13
  DDRB = DDRB & ~((1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5));
  DDRC = DDRC & ~((1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3));
  DDRD = DDRD & ~((1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) | (1<<DDD7));

  // Force tous les inputs pins en pullup (1)
  PORTB |= ((1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5));
  PORTC |= ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3));
  PORTD |= ((1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD5) | (1<<PORTD6) | (1<<PORTD7));

  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
  static unsigned long currentMillis;
  currentMillis = millis();

  // SAS
  // Interupt 3/12
  static KnobJoy yawTrim(I2C_DATA, 3, 12);
  yawTrim.runIndefiniteLeftRight(BUTTON_INDEX[BTN_IDX_YAW_TRIM_LEFT], BUTTON_INDEX[BTN_IDX_YAW_TRIM_RIGHT], &currentMillis);
  // D9
  static AutoReleaseSwitch monitorTestLSwitch(bitRead(PINB, PINB1), I2C_DATA, BUTTON_INDEX[BTN_IDX_MONITOR_TEST_LEFT]);
  monitorTestLSwitch.run(bitRead(PINB, PINB1), &currentMillis, BUTTON_INDEX[BTN_IDX_MONITOR_TEST_OFF]);
  // D10
  static AutoReleaseSwitch monitorTestRSwitch(bitRead(PINB, PINB2), I2C_DATA, BUTTON_INDEX[BTN_IDX_MONITOR_TEST_RIGHT]);
  monitorTestRSwitch.run(bitRead(PINB, PINB2), &currentMillis, BUTTON_INDEX[BTN_IDX_MONITOR_TEST_OFF]);
  // D4
  static PushButton toTrimButton(I2C_DATA, BUTTON_INDEX[BTN_IDX_TO_TRIM]);  
  toTrimButton.run(bitRead(PIND, PIND4));

  // SAS Engage: même bouton pour ON et OFF
  // D5
  // static AutoReleaseSwitch yawSasEngageLeft(bitRead(PIND, PIND5), I2C_DATA, BUTTON_INDEX[BTN_IDX_YAW_SAS_ENGAGE_LEFT]);
  // yawSasEngageLeft.run(bitRead(PIND, PIND5), &currentMillis, BUTTON_INDEX[BTN_IDX_YAW_SAS_ENGAGE_LEFT]);
  static PushButton yawSasEngageLeft(I2C_DATA, BUTTON_INDEX[BTN_IDX_YAW_SAS_ENGAGE_LEFT]);  
  yawSasEngageLeft.run(bitRead(PIND, PIND5));
  // D6
  // static AutoReleaseSwitch yawSasEngageRight(bitRead(PIND, PIND6), I2C_DATA, BUTTON_INDEX[BTN_IDX_YAW_SAS_ENGAGE_RIGHT]);
  // yawSasEngageRight.run(bitRead(PIND, PIND6), &currentMillis, BUTTON_INDEX[BTN_IDX_YAW_SAS_ENGAGE_RIGHT]);
  static PushButton yawSasEngageRight(I2C_DATA, BUTTON_INDEX[BTN_IDX_YAW_SAS_ENGAGE_RIGHT]);  
  yawSasEngageRight.run(bitRead(PIND, PIND6));
  // D7
  // static AutoReleaseSwitch pitchSasEngageLeft(bitRead(PIND, PIND7), I2C_DATA, BUTTON_INDEX[BTN_IDX_PITCH_SAS_ENGAGE_LEFT]);
  // pitchSasEngageLeft.run(bitRead(PIND, PIND7), &currentMillis, BUTTON_INDEX[BTN_IDX_PITCH_SAS_ENGAGE_LEFT]);
  static PushButton pitchSasEngageLeft(I2C_DATA, BUTTON_INDEX[BTN_IDX_PITCH_SAS_ENGAGE_LEFT]);  
  pitchSasEngageLeft.run(bitRead(PIND, PIND7));
  // D8
  // static AutoReleaseSwitch pitchSasEngageRight(bitRead(PINB, PINB0), I2C_DATA, BUTTON_INDEX[BTN_IDX_PITCH_SAS_ENGAGE_RIGHT]);
  // pitchSasEngageRight.run(bitRead(PINB, PINB0), &currentMillis, BUTTON_INDEX[BTN_IDX_PITCH_SAS_ENGAGE_RIGHT]);
  static PushButton pitchSasEngageRight(I2C_DATA, BUTTON_INDEX[BTN_IDX_PITCH_SAS_ENGAGE_RIGHT]);  
  pitchSasEngageRight.run(bitRead(PINB, PINB0));

  // AUX LTG
  // A3
  static PushButton fireDetect(I2C_DATA, BUTTON_INDEX[BTN_IDX_FIRE_DETECT]);  
  fireDetect.run(bitRead(PINC, PINC3));
  
  // A2
  static PushButton signalLightsTest(I2C_DATA, BUTTON_INDEX[BTN_IDX_SIGNAL_LIGHTS_TEST]);  
  signalLightsTest.run(bitRead(PINC, PINC2));

  // D13, même bouton pour OVERRIDE et NORM
  static AutoReleaseSwitch harsOverride(bitRead(PINB, PINB5), I2C_DATA, BUTTON_INDEX[BTN_IDX_HARS_SAS_OVERRIDE]);
  harsOverride.run(bitRead(PINB, PINB5), &currentMillis, BUTTON_INDEX[BTN_IDX_HARS_SAS_OVERRIDE]);
  
  // Encoder 2/11
  static KnobJoy refuelStatusLts(I2C_DATA, 2, 11);
  refuelStatusLts.runIndefiniteLeftRight(BUTTON_INDEX[BTN_IDX_REFUEL_LTS_DIM], BUTTON_INDEX[BTN_IDX_REFUEL_LTS_BRT], &currentMillis);
  
  // D1
  static AutoReleaseSwitch nvisLtsTop(bitRead(PIND, PIND1), I2C_DATA, BUTTON_INDEX[BTN_IDX_NVIS_LTS_TOP]);
  nvisLtsTop.run(bitRead(PIND, PIND1), &currentMillis, BUTTON_INDEX[BTN_IDX_NVIS_LTS_ALL]);
  
  // A0
  static AutoReleaseSwitch nvisLtsOff(bitRead(PINC, PINC0), I2C_DATA, BUTTON_INDEX[BTN_IDX_NVIS_LTS_OFF]);
  nvisLtsOff.run(bitRead(PINC, PINC0), &currentMillis, BUTTON_INDEX[BTN_IDX_NVIS_LTS_ALL]);
}
