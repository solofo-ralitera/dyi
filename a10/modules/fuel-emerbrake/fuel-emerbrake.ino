/*******************************
Fuel panel
*******************************/

#include <Wire.h>
#include "PushButton.h"
#include "AutoReleaseSwitch.h"
#include "KnobJoy.h"

// Adresse I2C du module
#define I2C_ADDRESS 3
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 3
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
};

// Fuel Panel
#define BTN_IDX_LIGHTING_DIAL_LEFT 0
#define BTN_IDX_LIGHTING_DIAL_RIGHT 1
#define BTN_IDX_BOOST_PUMPS_WING_L 2
#define BTN_IDX_BOOST_PUMPS_WING_R 3
#define BTN_IDX_BOOST_PUMPS_MAIN_L 4
#define BTN_IDX_BOOST_PUMPS_MAIN_R 5
#define BTN_IDX_FILL_DISABLE_WING_L 6
#define BTN_IDX_FILL_DISABLE_WING_R 7
#define BTN_IDX_FILL_DISABLE_MAIN_L 8
#define BTN_IDX_FILL_DISABLE_MAIN_R 9
#define BTN_IDX_EXT_TKS_WING 10
#define BTN_IDX_EXT_TKS_FUS 11
#define BTN_IDX_TK_GATE_OPEN 12
#define BTN_IDX_CROSS_FEED 13
#define BTN_IDX_RCVR_OPEN 14
#define BTN_IDX_SEAT_UP 15
#define BTN_IDX_SEAT_DOWN 16
#define BTN_IDX_EMER_BRAKE 17

// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[18][2] = {
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
};

void setup() {
  // Serial.begin(9600);

  // Force les digitals pins des ports B/C/D en configuration entrée (0), 
  DDRB = DDRB & ~((1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5));
  DDRC = DDRC & ~((1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3));
  DDRD = DDRD & ~((1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) | (1<<DDD7));

  // Force tous les inputs pins en pullup (1)
  PORTB |= ((1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5));
  PORTC |= ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3));
  PORTD |= ((1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD5) | (1<<PORTD6) | (1<<PORTD7));

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

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

  //////// Fuel Panel
  // Exterior lighting dial, Encoder 2/3
  static KnobJoy lightingDial(I2C_DATA, 2, 3);
  lightingDial.runIndefiniteLeftRight(BUTTON_INDEX[BTN_IDX_LIGHTING_DIAL_LEFT], BUTTON_INDEX[BTN_IDX_LIGHTING_DIAL_RIGHT], &currentMillis);
  
  // Boost pumps
  //  D9, Wing L
  static AutoReleaseSwitch boostPumpsWingL(bitRead(PINB, PINB1), I2C_DATA, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_WING_L]);
  boostPumpsWingL.run(bitRead(PINB, PINB1), &currentMillis, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_WING_L]);
  //  D8, Wing R
  static AutoReleaseSwitch boostPumpsWingR(bitRead(PINB, PINB0), I2C_DATA, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_WING_R]);
  boostPumpsWingR.run(bitRead(PINB, PINB0), &currentMillis, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_WING_R]);
  //  D10, Main L
  static AutoReleaseSwitch boostPumpsMainL(bitRead(PINB, PINB2), I2C_DATA, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_MAIN_L]);
  boostPumpsMainL.run(bitRead(PINB, PINB2), &currentMillis, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_MAIN_L]);
  //  D11, Main R
  static AutoReleaseSwitch boostPumpsMainR(bitRead(PINB, PINB3), I2C_DATA, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_MAIN_R]);
  boostPumpsMainR.run(bitRead(PINB, PINB3), &currentMillis, BUTTON_INDEX[BTN_IDX_BOOST_PUMPS_MAIN_R]);

  // Fill disable
  //  A1, Wing L
  static AutoReleaseSwitch fillDisableWingL(bitRead(PINC, PINC1), I2C_DATA, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_WING_L]);
  fillDisableWingL.run(bitRead(PINC, PINC1), &currentMillis, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_WING_L]);
  //  A0, Wing R
  static AutoReleaseSwitch fillDisableWingR(bitRead(PINC, PINC0), I2C_DATA, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_WING_R]);
  fillDisableWingR.run(bitRead(PINC, PINC0), &currentMillis, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_WING_R]);
  //  D12, Main L
  static AutoReleaseSwitch fillDisableMainL(bitRead(PINB, PINB4), I2C_DATA, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_MAIN_L]);
  fillDisableMainL.run(bitRead(PINB, PINB4), &currentMillis, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_MAIN_L]);
  //  A2, Main R
  static AutoReleaseSwitch fillDisableMainR(bitRead(PINC, PINC2), I2C_DATA, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_MAIN_R]);
  fillDisableMainR.run(bitRead(PINC, PINC2), &currentMillis, BUTTON_INDEX[BTN_IDX_FILL_DISABLE_MAIN_R]);

  // External tanks
  // D5, Wings
  static AutoReleaseSwitch extTksWing(bitRead(PIND, PIND5), I2C_DATA, BUTTON_INDEX[BTN_IDX_EXT_TKS_WING]);
  extTksWing.run(bitRead(PIND, PIND5), &currentMillis, BUTTON_INDEX[BTN_IDX_EXT_TKS_WING]);
  // D4, Fus
  static AutoReleaseSwitch extTksFus(bitRead(PIND, PIND4), I2C_DATA, BUTTON_INDEX[BTN_IDX_EXT_TKS_FUS]);
  extTksFus.run(bitRead(PIND, PIND4), &currentMillis, BUTTON_INDEX[BTN_IDX_EXT_TKS_FUS]);

  // D6, TK gate Open
  static AutoReleaseSwitch tkGateOpen(bitRead(PIND, PIND6), I2C_DATA, BUTTON_INDEX[BTN_IDX_TK_GATE_OPEN]);
  tkGateOpen.run(bitRead(PIND, PIND6), &currentMillis, BUTTON_INDEX[BTN_IDX_TK_GATE_OPEN]);

  // D7, TK gate Open
  static AutoReleaseSwitch crossFeed(bitRead(PIND, PIND7), I2C_DATA, BUTTON_INDEX[BTN_IDX_CROSS_FEED]);
  crossFeed.run(bitRead(PIND, PIND7), &currentMillis, BUTTON_INDEX[BTN_IDX_CROSS_FEED]);

  // D13, RCVR Open 
  static AutoReleaseSwitch receiverOpen(bitRead(PINB, PINB5), I2C_DATA, BUTTON_INDEX[BTN_IDX_RCVR_OPEN]);
  receiverOpen.run(bitRead(PINB, PINB5), &currentMillis, BUTTON_INDEX[BTN_IDX_RCVR_OPEN]);

  // D1
  static PushButton d1(I2C_DATA, BUTTON_INDEX[BTN_IDX_SEAT_DOWN]);
  d1.run(bitRead(PIND, PIND1));

  // D0
  static PushButton d0(I2C_DATA, BUTTON_INDEX[BTN_IDX_SEAT_UP]);
  d0.run(bitRead(PIND, PIND0));

  // A3
  static PushButton a3(I2C_DATA, BUTTON_INDEX[BTN_IDX_EMER_BRAKE]);
  a3.runToggle(bitRead(PINC, PINC3), &currentMillis);
}
