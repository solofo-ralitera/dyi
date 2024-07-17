/*******************************
LASTE Control Panel ans Throttle panel (24 bouttons)
  LASTE Control Panel
    EAC: Switch 2 positions (ON/OFF)
    Radar Altimeter: Switch 2 positions (NRM/DIS)
    Auto pilot Engage/Disengage: push button
    Auto pilot select: switch 3 positions (PATH/ALT-HDG/ALT)
  Throttle panel
    Langing Gear Warn: push button
    APU Start: switch 2 positions (ON/OFF)
    Engine Operate Switches L: switch 3 positions (IGN/NORM/MOTOR)
    Engine Operate Switches R: switch 3 positions (IGN/NORM/MOTOR)
    Engine fluel flow L: switch 2 positions (NORM/OVERRIDE)
    Engine fluel flow R: switch 2 positions (NORM/OVERRIDE)
    Flaps: switch 3 positions (UP/MVR/DN)
*******************************/

#include "PushButton.h"
#include "AutoReleaseSwitch.h"
#include <Wire.h>

// Adresse I2C du module
#define I2C_ADDRESS 1
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 3
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
};

// LASTE Control Panel
#define BTN_IDX_EAC_ON 0
#define BTN_IDX_EAC_OFF 1
#define BTN_IDX_RDR_ON 2
#define BTN_IDX_RDR_OFF 3
#define BTN_IDX_AUTOPILOT_ENGAGE 4
#define BTN_IDX_AUTOPILOT_PATH 5
#define BTN_IDX_AUTOPILOT_ALTHDG 6
#define BTN_IDX_AUTOPILOT_ALT 7

// Throttle panel
#define BTN_IDX_LANDING_GEAR_WARN 8
#define BTN_IDX_APU_START 9
#define BTN_IDX_APU_OFF 10
#define BTN_IDX_ENG_OPER_L_IGN 11
#define BTN_IDX_ENG_OPER_L_NORM 12
#define BTN_IDX_ENG_OPER_L_MOTOR 13
#define BTN_IDX_ENG_OPER_R_IGN 14
#define BTN_IDX_ENG_OPER_R_NORM 15
#define BTN_IDX_ENG_OPER_R_MOTOR 16
#define BTN_IDX_ENG_FUEL_FLOW_L_NORM 17
#define BTN_IDX_ENG_FUEL_FLOW_L_OVERRIDE 18
#define BTN_IDX_ENG_FUEL_FLOW_R_NORM 19
#define BTN_IDX_ENG_FUEL_FLOW_R_OVERRIDE 20
#define BTN_IDX_FLAPS_UP 21
#define BTN_IDX_FLAPS_MVR 22
#define BTN_IDX_FLAPS_DN 23


// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[24][2] = {
  // Laste panel
  {0, 0}, // BTN_IDX_EAC_ON
  {0, 1}, // BTN_IDX_EAC_OFF
  {0, 2}, // BTN_IDX_RDR_ON
  {0, 3}, // BTN_IDX_RDR_OFF
  {0, 4}, // BTN_IDX_AUTOPILOT_ENGAGE / DISENGAGE
  {0, 5}, // BTN_IDX_AUTOPILOT_PATH
  {0, 6}, // BTN_IDX_AUTOPILOT_ALTHDG
  {0, 7}, // BTN_IDX_AUTOPILOT_ALT
  //// Throttle panel
  {1, 0}, // BTN_IDX_LANDING_GEAR_WARN (test 4, 5)
  {1, 1}, // BTN_IDX_APU_START
  {1, 2}, // BTN_IDX_APU_OFF
  {1, 3}, // BTN_IDX_ENG_OPER_L_IGN
  {1, 4}, // BTN_IDX_ENG_OPER_L_NORM
  {1, 5}, // BTN_IDX_ENG_OPER_L_MOTOR
  {1, 6}, // BTN_IDX_ENG_OPER_R_IGN
  {1, 7}, // BTN_IDX_ENG_OPER_R_NORM
  {2, 0}, // BTN_IDX_ENG_OPER_R_MOTOR
  {2, 1}, // BTN_IDX_ENG_FUEL_FLOW_L_NORM
  {2, 2}, // BTN_IDX_ENG_FUEL_FLOW_L_OVERRIDE
  {2, 3}, // BTN_IDX_ENG_FUEL_FLOW_R_NORM
  {2, 4}, // BTN_IDX_ENG_FUEL_FLOW_R_OVERRIDE
  {2, 5}, // BTN_IDX_FLAPS_UP
  {2, 6}, // BTN_IDX_FLAPS_MVR
  {2, 7}, //BTN_IDX_FLAPS_DN
};

void setup() {
  // Serial.begin(9600);

  /**
  // DDRX => Registre de config des ports entrée/sortie
  //          X: B/C/D, ex: DDRB
  //    DDXN => index de chaque bit (= pin, cf pinout) du registre
  //        0 = entrée, 1 = sortie
  //        ex: DDB0 correspond au pin 8 (PB0) du nano
  **/
  // Force les digitals pins des ports B/C/D en configuration entrée (0), 
  // !!! pin 0 et 1 non disponible quand Serial est activé
  // !!! pin A4 et A5 pour l'I2C
  DDRB = DDRB & ~((1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5));
  DDRC = DDRC & ~((1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3));
  DDRD = DDRD & ~((1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) | (1<<DDD7));

  /**
  //  Pour un pin configuré en entrée: pour activer la resistance de pullup: set PORTXN à 1
  **/
  // Force tous les inputs pins en pullup (1)
  PORTB |= ((1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5));
  PORTC |= ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3));
  PORTD |= ((1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD5) | (1<<PORTD6) | (1<<PORTD7));

  //      
  //
  // PINX => Registre pour lire l'état des pin d'entrée (input)
  //          X: B/C/D
  //    PINXN => pour lire l'état d'entrée, 0 LOW, 1 HIGH
  //
  //
  // PORTX => Registre pour lire l'état des pin d'entrée (input)
  //          X: B/C/D
  //    PORTXN => pour ecrire l'état de sortie
  //

  
  // put your setup code here, to run once:
  Wire.begin(I2C_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Set the request event handler
}

void requestEvent()
{
  Wire.write(I2C_DATA, BUFFER_SIZE);
}

void loop() {
  static unsigned long currentMillis;
  currentMillis = millis();

  //////// LASTE Panel
  //  D7
  static AutoReleaseSwitch eacSwitch(bitRead(PIND, PIND7), I2C_DATA, BUTTON_INDEX[BTN_IDX_EAC_ON]);
  eacSwitch.run(bitRead(PIND, PIND7), &currentMillis, BUTTON_INDEX[BTN_IDX_EAC_OFF]);
  // D6
  static AutoReleaseSwitch rdrSwitch(bitRead(PIND, PIND6), I2C_DATA, BUTTON_INDEX[BTN_IDX_RDR_ON]);
  rdrSwitch.run(bitRead(PIND, PIND6), &currentMillis, BUTTON_INDEX[BTN_IDX_RDR_OFF]);
  // D4
  static PushButton autoPilotButton(I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ENGAGE]);  
  autoPilotButton.run(bitRead(PIND, PIND4));
  // D2
  static AutoReleaseSwitch autoPilotPathSwitch(bitRead(PIND, PIND2), I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_PATH]);
  autoPilotPathSwitch.run(bitRead(PIND, PIND2), &currentMillis, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALTHDG]);
  //D3
  static AutoReleaseSwitch autoPilotAltSwitch(bitRead(PIND, PIND3), I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALT]);
  autoPilotAltSwitch.run(bitRead(PIND, PIND3), &currentMillis, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALTHDG]);
  // D8
  static AutoReleaseSwitch flapsUpSwitch(bitRead(PINB, PINB0), I2C_DATA, BUTTON_INDEX[BTN_IDX_FLAPS_UP]);
  flapsUpSwitch.run(bitRead(PINB, PINB0), &currentMillis, BUTTON_INDEX[BTN_IDX_FLAPS_MVR]);
  // D5
  static AutoReleaseSwitch flapsDownSwitch(bitRead(PIND, PIND5), I2C_DATA, BUTTON_INDEX[BTN_IDX_FLAPS_DN]);
  flapsDownSwitch.run(bitRead(PIND, PIND5), &currentMillis, BUTTON_INDEX[BTN_IDX_FLAPS_MVR]);

  //////// Throttle Panel
  static PushButton landingGearButton(I2C_DATA, BUTTON_INDEX[BTN_IDX_LANDING_GEAR_WARN]);
  landingGearButton.run(bitRead(PINC, PINC2));

  static AutoReleaseSwitch apuStartSwitch(bitRead(PINC, PINC1), I2C_DATA, BUTTON_INDEX[BTN_IDX_APU_START]);
  apuStartSwitch.run(bitRead(PINC, PINC1), &currentMillis, BUTTON_INDEX[BTN_IDX_APU_OFF]);

  static AutoReleaseSwitch engOperLIgnSwitch(bitRead(PINB, PINB5), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_IGN]);
  engOperLIgnSwitch.run(bitRead(PINB, PINB5), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_NORM]);

  static AutoReleaseSwitch engOperLMotorSwitch(bitRead(PINC, PINC0), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_MOTOR]);
  engOperLMotorSwitch.run(bitRead(PINC, PINC0), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_NORM]);

  static AutoReleaseSwitch engOperRIgnSwitch(bitRead(PINB, PINB3), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_IGN]);
  engOperRIgnSwitch.run(bitRead(PINB, PINB3), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_NORM]);

  static AutoReleaseSwitch engOperRMotorSwitch(bitRead(PINB, PINB4), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_MOTOR]);
  engOperRMotorSwitch.run(bitRead(PINB, PINB4), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_NORM]);

  static AutoReleaseSwitch engFlowLSwitch(bitRead(PINB, PINB2), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_L_NORM]);
  engFlowLSwitch.run(bitRead(PINB, PINB2), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_L_OVERRIDE]);

  static AutoReleaseSwitch engFlowRSwitch(bitRead(PINB, PINB1), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_R_NORM]);
  engFlowRSwitch.run(bitRead(PINB, PINB1), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_R_OVERRIDE]);
}
