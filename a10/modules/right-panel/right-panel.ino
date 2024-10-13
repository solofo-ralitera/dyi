/*******************************
CDU keyboard
*******************************/
#define DCSBIOS_IRQ_SERIAL
// #define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

byte I2C_DATA[1] = {
  B00000000,
};

void sendDcsCommand(const char* msg, const char* args) {
  while(!DcsBios::tryToSendDcsBiosMessage(msg, args));
}

#include "caution-panel.h"
#include "cdu-keyboard.h"
#include "cdu-keyboard-other.h"
#include "cdu-keyboard-num.h"
#include "cdu-keyboard-alpha.h"
#include "light-control.h"
#include "aap.h"

// STALL SYS
DcsBios::IntegerBuffer cp1(A_10C_CL_K1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 0, 2, newValue);
});
// APU GEN
DcsBios::IntegerBuffer cp2(A_10C_CL_L1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 1, 2, newValue);
});
// L-CONV
DcsBios::IntegerBuffer cp3(A_10C_CL_K2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 2, 2, newValue);
});
// L-GEN
DcsBios::IntegerBuffer cp4(A_10C_CL_L2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 3, 2, newValue);
});
// R-CONV
DcsBios::IntegerBuffer cp5(A_10C_CL_K3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 4, 2, newValue);
});
// R-GEN
DcsBios::IntegerBuffer cp6(A_10C_CL_L3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 5, 2, newValue);
});
// CADC
DcsBios::IntegerBuffer cp7(A_10C_CL_K4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 6, 2, newValue);
});
// INST INV
DcsBios::IntegerBuffer cp8(A_10C_CL_L4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 7, 2, newValue);
});
// IFF MODE 4
DcsBios::IntegerBuffer cp9(A_10C_CL_I1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 0, 3, newValue);
});
// EAC !!
DcsBios::IntegerBuffer cp10(A_10C_CL_J1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 1, 3, newValue);
});
// L-MAIN FUEL LOW
DcsBios::IntegerBuffer cp11(A_10C_CL_I2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 2, 3, newValue);
});
// L-FUEL PRESS
DcsBios::IntegerBuffer cp12(A_10C_CL_J2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 3, 3, newValue);
});
// R-MAIN FUEL LOW
DcsBios::IntegerBuffer cp13(A_10C_CL_I3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 4, 3, newValue);
});
// R-FUEL PRESS
DcsBios::IntegerBuffer cp14(A_10C_CL_J3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 5, 3, newValue);
});
// L-R TKS UNEQUAL
DcsBios::IntegerBuffer cp15(A_10C_CL_I4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 6, 3, newValue);
});
// nav
DcsBios::IntegerBuffer cp16(A_10C_CL_J4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 7, 3, newValue);
});
// GCAS
DcsBios::IntegerBuffer cp17(A_10C_CL_G1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 0, 4, newValue);
});
// LASTE !!!
DcsBios::IntegerBuffer cp18(A_10C_CL_H1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 1, 4, newValue);
});
// L-MAIN PUMP
DcsBios::IntegerBuffer cp19(A_10C_CL_G2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 2, 4, newValue);
});
// L-WING PUMP !!!
DcsBios::IntegerBuffer cp20(A_10C_CL_H2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 3, 4, newValue);
});
// R-MAIN PUMP
DcsBios::IntegerBuffer cp21(A_10C_CL_G3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 4, 4, newValue);
});
// R-WING PUMP
DcsBios::IntegerBuffer cp22(A_10C_CL_H3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 5, 4, newValue);
});
// VOID 2
DcsBios::IntegerBuffer cp23(A_10C_CL_G4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 6, 4, newValue);
});
// HARS !!!
DcsBios::IntegerBuffer cp24(A_10C_CL_H4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 7, 4, newValue);
});
// PITCH SAS
DcsBios::IntegerBuffer cp25(A_10C_CL_E1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 0, 5, newValue);
});
// YAW SAS
DcsBios::IntegerBuffer cp26(A_10C_CL_F1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 1, 5, newValue);
});
// L-ENG HOT
DcsBios::IntegerBuffer cp27(A_10C_CL_E2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 2, 5, newValue);
});
// L-ENG OIL PRESS
DcsBios::IntegerBuffer cp28(A_10C_CL_F2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 3, 5, newValue);
});
// R-ENG HOT
DcsBios::IntegerBuffer cp29(A_10C_CL_E3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 4, 5, newValue);
});
// R-ENG OIL PRESS
DcsBios::IntegerBuffer cp30(A_10C_CL_F3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 5, 5, newValue);
});
// WINDSHIELD HOT
DcsBios::IntegerBuffer cp31(A_10C_CL_E4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 6, 5, newValue);
});
// CICU
DcsBios::IntegerBuffer cp32(A_10C_CL_F4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 7, 5, newValue);
});
// ELEV DISENG
DcsBios::IntegerBuffer cp33(A_10C_CL_C1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 0, 6, newValue);
});
// AIL DISENG
DcsBios::IntegerBuffer cp34(A_10C_CL_D1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 1, 6, newValue);
});
// void 1
DcsBios::IntegerBuffer cp35(A_10C_CL_C2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 2, 6, newValue);
});
// L-AIL TAB
DcsBios::IntegerBuffer cp36(A_10C_CL_D2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 3, 6, newValue);
});
// SEAT NOT ARMED
DcsBios::IntegerBuffer cp37(A_10C_CL_C3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 4, 6, newValue);
});
// R-AIL TAB
DcsBios::IntegerBuffer cp38(A_10C_CL_D3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 5, 6, newValue);
});
// BLEED AIR LEEK
DcsBios::IntegerBuffer cp39(A_10C_CL_C4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 6, 6, newValue);
});
// SERVICE AIR HOT
DcsBios::IntegerBuffer cp40(A_10C_CL_D4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 7, 6, newValue);
});
// ENG START CYCLE
DcsBios::IntegerBuffer cp41(A_10C_CL_A1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 0, 7, newValue);
});
// ANTI-SKID
DcsBios::IntegerBuffer cp42(A_10C_CL_B1, [](unsigned int newValue) {
  cautionPanel.setLed(0, 1, 7, newValue);
});
// L-HYD PRESS
DcsBios::IntegerBuffer cp43(A_10C_CL_A2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 2, 7, newValue);
});
// L-HYD RES
DcsBios::IntegerBuffer cp44(A_10C_CL_B2, [](unsigned int newValue) {
  cautionPanel.setLed(0, 3, 7, newValue);
});
// R-HYD PRESS
DcsBios::IntegerBuffer cp45(A_10C_CL_A3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 4, 7, newValue);
});
// R-HYD RES
DcsBios::IntegerBuffer cp46(A_10C_CL_B3, [](unsigned int newValue) {
  cautionPanel.setLed(0, 5, 7, newValue);
});
// GUN UNSAFE
DcsBios::IntegerBuffer cp47(A_10C_CL_A4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 6, 7, newValue);
});
// OXY LOW
DcsBios::IntegerBuffer cp48(A_10C_CL_B4, [](unsigned int newValue) {
  cautionPanel.setLed(0, 7, 7, newValue);
});

void setup() {
  // Serial.begin(9600);
  setupCautionPanel();

  setupCduKeyboard();
  setupCduKeyboardOther();
  setupCduKeyboardNum();
  setupCduKeyboardAlpha();

  setupLightControl();
  setupAap();

  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
  
  runCduKeyboard();
  runCduKeyboardOther();
  runCduKeyboardNum();
  runCduKeyboardAlpha();

  runLightControl();
  runAap();
}
