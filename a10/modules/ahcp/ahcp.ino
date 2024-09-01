/*******************************
Fuel panel
*******************************/

#include <Wire.h>
#include "PushButton.h"
#include "AutoReleaseSwitch.h"
#include "KnobJoy.h"

// Adresse I2C du module
#define I2C_ADDRESS 4
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 3
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
};

// Ahcp panel
#define BTN_IDX_MASTER_ARM 0
#define BTN_IDX_MASTER_TRAIN 1
#define BTN_IDX_GUNPAC_ARM 2
#define BTN_IDX_GUNPAC_GUNARM 3
#define BTN_IDX_LASER_ARM 4
#define BTN_IDX_LASER_TRAIN 5
#define BTN_IDX_TGP 6
#define BTN_IDX_ALTSCE_BARO 7
#define BTN_IDX_ALTSCE_RADAR 8
#define BTN_IDX_HUDMODE_DAY_NIGHT 9
#define BTN_IDX_HUDMODE_NORM_STBY 10
#define BTN_IDX_CICU 11
#define BTN_IDX_JTRS 12
#define BTN_IFCC_ON 13
#define BTN_IFCC_TEST 14
#define BTN_LANDING_LIGHTS_ON 15
#define BTN_LANDING_LIGHTS_TAXI 16
#define BTN_ANTI_SKID 17
#define BTN_DOWNLOCK_OVERRIDE 18
#define BTN_LANDING_GEAR_DOWN 19
#define BTN_LANDING_GEAR_UP 20

// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[20][2] = {
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

  // !!!!!!!!!!!!!!!!!!
  // For analog pins A6 and A7, add external 40k pullup resistors

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  
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

  // D11
  static PushButton masterArm(I2C_DATA, BUTTON_INDEX[BTN_IDX_MASTER_ARM]);
  masterArm.run(bitRead(PINB, PINB3));
  // D12
  static PushButton masterTrain(I2C_DATA, BUTTON_INDEX[BTN_IDX_MASTER_TRAIN]);
  masterTrain.run(bitRead(PINB, PINB4));

  // A7 !!! Analog
  static PushButton gunpacArm(I2C_DATA, BUTTON_INDEX[BTN_IDX_GUNPAC_ARM]);
  gunpacArm.run(analogRead(A7) < 511 ? 0 : 1); // must fit in byte
  // A6 !! Analog
  static PushButton gunpacGunArm(I2C_DATA, BUTTON_INDEX[BTN_IDX_GUNPAC_GUNARM]);
  gunpacGunArm.run(analogRead(A6) < 511 ? 0 : 1); // must fit in byte

  // D9
  static PushButton laserArm(I2C_DATA, BUTTON_INDEX[BTN_IDX_LASER_ARM]);
  laserArm.run(bitRead(PINB, PINB1));
  // D10
  static PushButton laserTrain(I2C_DATA, BUTTON_INDEX[BTN_IDX_LASER_TRAIN]);
  laserTrain.run(bitRead(PINB, PINB2));

  // D8
  static AutoReleaseSwitch tgp(bitRead(PINB, PINB0), I2C_DATA, BUTTON_INDEX[BTN_IDX_TGP]);
  tgp.run(bitRead(PINB, PINB0), &currentMillis, BUTTON_INDEX[BTN_IDX_TGP]);

  // D3
  static PushButton altSceBaro(I2C_DATA, BUTTON_INDEX[BTN_IDX_ALTSCE_BARO]);
  altSceBaro.run(bitRead(PIND, PIND3));
  // D5
  static PushButton altSceRadar(I2C_DATA, BUTTON_INDEX[BTN_IDX_ALTSCE_RADAR]);
  altSceRadar.run(bitRead(PIND, PIND5));

  // D6
  static AutoReleaseSwitch hudModeDayNight(bitRead(PIND, PIND6), I2C_DATA, BUTTON_INDEX[BTN_IDX_HUDMODE_DAY_NIGHT]);
  hudModeDayNight.run(bitRead(PIND, PIND6), &currentMillis, BUTTON_INDEX[BTN_IDX_HUDMODE_DAY_NIGHT]);
  // D7
  static AutoReleaseSwitch hudModeNormStby(bitRead(PIND, PIND7), I2C_DATA, BUTTON_INDEX[BTN_IDX_HUDMODE_NORM_STBY]);
  hudModeNormStby.run(bitRead(PIND, PIND7), &currentMillis, BUTTON_INDEX[BTN_IDX_HUDMODE_NORM_STBY]);
  
  // D4
  static AutoReleaseSwitch cicu(bitRead(PIND, PIND4), I2C_DATA, BUTTON_INDEX[BTN_IDX_CICU]);
  cicu.run(bitRead(PIND, PIND4), &currentMillis, BUTTON_INDEX[BTN_IDX_CICU]);
  // D2
  static AutoReleaseSwitch jtrs(bitRead(PIND, PIND2), I2C_DATA, BUTTON_INDEX[BTN_IDX_JTRS]);
  jtrs.run(bitRead(PIND, PIND2), &currentMillis, BUTTON_INDEX[BTN_IDX_JTRS]);

  // D0
  static PushButton ifccOn(I2C_DATA, BUTTON_INDEX[BTN_IFCC_ON]);
  ifccOn.run(bitRead(PIND, PIND0));
  // D1
  static PushButton ifccTest(I2C_DATA, BUTTON_INDEX[BTN_IFCC_TEST]);
  ifccTest.run(bitRead(PIND, PIND1));

  // A3
  static PushButton landingLightsOn(I2C_DATA, BUTTON_INDEX[BTN_LANDING_LIGHTS_ON]);
  landingLightsOn.run(bitRead(PINC, PINC3));
  // A2
  static PushButton landingLightsTaxi(I2C_DATA, BUTTON_INDEX[BTN_LANDING_LIGHTS_TAXI]);
  landingLightsTaxi.run(bitRead(PINC, PINC2));

  // A1
  static AutoReleaseSwitch antiSkid(bitRead(PINC, PINC1), I2C_DATA, BUTTON_INDEX[BTN_ANTI_SKID]);
  antiSkid.run(bitRead(PINC, PINC1), &currentMillis, BUTTON_INDEX[BTN_ANTI_SKID]);

  // D13
  static PushButton downLockOverride(I2C_DATA, BUTTON_INDEX[BTN_DOWNLOCK_OVERRIDE]);
  downLockOverride.run(bitRead(PINB, PINB5));
  
  // A0
  static PushButton landingGear(I2C_DATA, BUTTON_INDEX[BTN_LANDING_GEAR_DOWN]);
  landingGear.run(bitRead(PINC, PINC0));
}
