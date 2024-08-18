#ifndef ledMatrix_h
#define ledMatrix_h

#include "LedControl.h"
/**********************************************
    |0, 0|0, 1|0, 2|0,3 |0, 4|0, 5|0, 6|0, 7|
    |1, 0|1, 1|    |    |    |    |1, 6|1, 7|
    |2,  |    |    |    |    |    |    |    |
    |3   |    |    |    |    |    |    |    |
    |4   |    |    |    |    |    |    |    |
    |5, 0|5, 1|5   |5   |5   |5   |5   |5   |
    |6, 0|6, 1|6   |6   |6   |6   |6   |6   |
    |7, 0|7, 1|    |    |    |    |    |    |
**********************************************/
//// Landing Gear & Flap panel
#define LED_MATRIX_LANDING_GEAR_L_SAFE 0, 7, 0 // Yellow
#define LED_MATRIX_LANDING_GEAR_N_SAFE 0, 6, 0 // Orange
#define LED_MATRIX_LANDING_GEAR_R_SAFE 0, 7, 1 // Red
#define LED_MATRIX_ANTISKID 0, 5, 0 // Brown
#define LED_MATRIX_HANDLE_GEAR_WARNING 0, 6, 1 // Black/white

// SAS Panel
#define LED_MATRIX_YAW_SAS_ENGAGE_L 0, 0, 7 // Orange
#define LED_MATRIX_YAW_SAS_ENGAGE_R 0, 1, 7 // Yellow
#define LED_MATRIX_PITCH_SAS_ENGAGE_L 0, 0, 6 // Green
#define LED_MATRIX_PITCH_SAS_ENGAGE_R 0, 1, 6 // Blue

// LASTE
#define LED_MATRIX_EAC 0, 5, 1 // Red

LedControl ledMatrix = LedControl(51, 52, 53, 1);

void ledMatrixInit() {
    ledMatrix.shutdown(0, false);
    ledMatrix.setIntensity(0,8);
    ledMatrix.clearDisplay(0);
}

void ledMatrixSet(int addr, int row, int col , boolean state) {
  ledMatrix.setLed(addr, row, col, state);
}
#endif

