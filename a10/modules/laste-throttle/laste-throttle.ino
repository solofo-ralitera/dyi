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
#define BUFFER_SIZE 2
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
};

// LASTE Control Panel
#define BTN_IDX_EAC_ON 0
#define BTN_IDX_RDR_NRM 1
#define BTN_IDX_AUTOPILOT_ENGAGE 2
#define BTN_IDX_AUTOPILOT_PATH 3
#define BTN_IDX_AUTOPILOT_ALT 4
// Throttle panel
#define BTN_IDX_LANDING_GEAR_WARN 5
#define BTN_IDX_APU_START 6
#define BTN_IDX_ENG_OPER_L_IGN 7
#define BTN_IDX_ENG_OPER_L_MOTOR 8
#define BTN_IDX_ENG_OPER_R_IGN 9
#define BTN_IDX_ENG_OPER_R_MOTOR 10
#define BTN_IDX_ENG_FUEL_FLOW_L_NORM 11
#define BTN_IDX_ENG_FUEL_FLOW_R_NORM 12
#define BTN_IDX_FLAPS_UP 13
#define BTN_IDX_FLAPS_DN 14


// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[15][2] = {
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
  // static AutoReleaseSwitch eacSwitch(bitRead(PIND, PIND7), I2C_DATA, BUTTON_INDEX[BTN_IDX_EAC_ON]);
  // eacSwitch.run(bitRead(PIND, PIND7), &currentMillis, BUTTON_INDEX[BTN_IDX_EAC_OFF]);
  static PushButton eac(I2C_DATA, BUTTON_INDEX[BTN_IDX_EAC_ON]);  
  eac.run(bitRead(PIND, PIND7));

  // D6
  // static AutoReleaseSwitch rdrSwitch(bitRead(PIND, PIND6), I2C_DATA, BUTTON_INDEX[BTN_IDX_RDR_ON]);
  // rdrSwitch.run(bitRead(PIND, PIND6), &currentMillis, BUTTON_INDEX[BTN_IDX_RDR_OFF]);
  static PushButton rdr(I2C_DATA, BUTTON_INDEX[BTN_IDX_RDR_NRM]);  
  rdr.run(bitRead(PIND, PIND6));
  // D4
  static AutoReleaseSwitch autoPilotButton(bitRead(PIND, PIND4), I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ENGAGE]);
  autoPilotButton.run(bitRead(PIND, PIND4), &currentMillis);
  // static PushButton autoPilotButton(I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ENGAGE]);  
  // autoPilotButton.run(bitRead(PIND, PIND4));
  // D2
  // static AutoReleaseSwitch autoPilotPathSwitch(bitRead(PIND, PIND2), I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_PATH]);
  // autoPilotPathSwitch.run(bitRead(PIND, PIND2), &currentMillis, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALTHDG]);
  static PushButton autoPilotPath(I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_PATH]);  
  autoPilotPath.run(bitRead(PIND, PIND2));
  //D3
  // static AutoReleaseSwitch autoPilotAltSwitch(bitRead(PIND, PIND3), I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALT]);
  // autoPilotAltSwitch.run(bitRead(PIND, PIND3), &currentMillis, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALTHDG]);
  static PushButton autoPilotAlt(I2C_DATA, BUTTON_INDEX[BTN_IDX_AUTOPILOT_ALT]);  
  autoPilotAlt.run(bitRead(PIND, PIND3));
  
  // D8
  // static AutoReleaseSwitch flapsUpSwitch(bitRead(PINB, PINB0), I2C_DATA, BUTTON_INDEX[BTN_IDX_FLAPS_UP]);
  // flapsUpSwitch.run(bitRead(PINB, PINB0), &currentMillis, BUTTON_INDEX[BTN_IDX_FLAPS_MVR]);
  static PushButton flapsUp(I2C_DATA, BUTTON_INDEX[BTN_IDX_FLAPS_UP]);  
  flapsUp.run(bitRead(PINB, PINB0));

  // D5
  // static AutoReleaseSwitch flapsDownSwitch(bitRead(PIND, PIND5), I2C_DATA, BUTTON_INDEX[BTN_IDX_FLAPS_DN]);
  // flapsDownSwitch.run(bitRead(PIND, PIND5), &currentMillis, BUTTON_INDEX[BTN_IDX_FLAPS_MVR]);
  static PushButton flapsDown(I2C_DATA, BUTTON_INDEX[BTN_IDX_FLAPS_DN]);  
  flapsDown.run(bitRead(PIND, PIND5));

  //////// Throttle Panel
  static PushButton landingGearButton(I2C_DATA, BUTTON_INDEX[BTN_IDX_LANDING_GEAR_WARN]);
  landingGearButton.run(bitRead(PINC, PINC2));

  // static AutoReleaseSwitch apuStartSwitch(bitRead(PINC, PINC1), I2C_DATA, BUTTON_INDEX[BTN_IDX_APU_START]);
  // apuStartSwitch.run(bitRead(PINC, PINC1), &currentMillis, BUTTON_INDEX[BTN_IDX_APU_OFF]);
  static PushButton apuStart(I2C_DATA, BUTTON_INDEX[BTN_IDX_APU_START]);  
  apuStart.run(bitRead(PINC, PINC1));

  // static PushButton engOperLIgn(bitRead(PINB, PINB5), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_IGN]);
  // engOperLIgn.run(bitRead(PINB, PINB5), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_NORM]);
  static PushButton engOperLIgn(I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_IGN]);  
  engOperLIgn.run(bitRead(PINB, PINB5));

  // static AutoReleaseSwitch engOperRIgnSwitch(bitRead(PINB, PINB3), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_IGN]);
  // engOperRIgnSwitch.run(bitRead(PINB, PINB3), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_NORM]);
  static PushButton engOperRIgn(I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_IGN]);  
  engOperRIgn.run(bitRead(PINB, PINB3));

  // static AutoReleaseSwitch engOperLMotorSwitch(bitRead(PINC, PINC0), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_MOTOR]);
  // engOperLMotorSwitch.run(bitRead(PINC, PINC0), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_NORM]);
  static PushButton engOperLMotor(I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_L_MOTOR]);  
  engOperLMotor.run(bitRead(PINC, PINC0));

  // static AutoReleaseSwitch engOperRMotorSwitch(bitRead(PINB, PINB4), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_MOTOR]);
  // engOperRMotorSwitch.run(bitRead(PINB, PINB4), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_NORM]);
  static PushButton engOperRMotor(I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_OPER_R_MOTOR]);  
  engOperRMotor.run(bitRead(PINB, PINB4));

  /// static AutoReleaseSwitch engFlowLSwitch(bitRead(PINB, PINB2), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_L_NORM]);
  // engFlowLSwitch.run(bitRead(PINB, PINB2), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_L_OVERRIDE]);
  static PushButton engFlowL(I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_L_NORM]);  
  engFlowL.run(bitRead(PINB, PINB2));

  // static AutoReleaseSwitch engFlowRSwitch(bitRead(PINB, PINB1), I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_R_NORM]);
  // engFlowRSwitch.run(bitRead(PINB, PINB1), &currentMillis, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_R_OVERRIDE]);
  static PushButton engFlowR(I2C_DATA, BUTTON_INDEX[BTN_IDX_ENG_FUEL_FLOW_R_NORM]);  
  engFlowR.run(bitRead(PINB, PINB1));
}
