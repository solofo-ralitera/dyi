// #define DCSBIOS_IRQ_SERIAL
#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_DISABLE_SERVO
#include "DcsBios.h"

#include <math.h>

// Load TFT driver library
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft;           // A single instance is used for all displays

#include "hsi.h"

DcsBios::IntegerBuffer hsiHdgBuffer(A_10C_HSI_HDG, [](unsigned int newValue) {
  hsiCurrentAngleHeading = map(newValue, 65535, 0, 359, 1);
  drawHsi();
});

DcsBios::IntegerBuffer hsiBearing1Buffer(A_10C_HSI_BEARING1, [](unsigned int newValue) {
  hsiCurrentAngleBearing1 = map(newValue, 65535, 0, 359, 1);
  drawHsi();
});

DcsBios::IntegerBuffer hsiBearing2Buffer(A_10C_HSI_BEARING2, [](unsigned int newValue) {
  hsiCurrentAngleBearing2 = map(newValue, 65535, 0, 359, 1);
  drawHsi();
});

float hsiCourse1 = 0;
float hsiCourse10 = 0;
// Course unité
DcsBios::IntegerBuffer hsiCcBBuffer(A_10C_HSI_CC_B, [](unsigned int newValue) {
  hsiCourse1 = map(newValue, 65535, 0, 99, 0) / 10;
  hsiCurrentAngleCourseArrow = hsiCourse1 + (hsiCourse10 * 10);
  drawHsi();
});
// Course dizaine
DcsBios::IntegerBuffer hsiCcABuffer(A_10C_HSI_CC_A, [](unsigned int newValue) {
  hsiCourse10 = map(newValue, 65535, 0, 359, 0) / 10;
  hsiCurrentAngleCourseArrow = hsiCourse1 + (hsiCourse10 * 10);
  // drawHsi();
});

DcsBios::IntegerBuffer hsiDeviationBuffer(A_10C_HSI_DEVIATION, [](unsigned int newValue) {
  hsiCurrentDeviation = map(newValue, 0, 65535, 55, -55);
  drawHsi();
});

DcsBios::IntegerBuffer hsiBearingFlagBuffer(A_10C_HSI_BEARING_FLAG, [](unsigned int newValue) {
  hsiCurrentBearingFlag = newValue ? true : false;
  drawHsi();
});

DcsBios::IntegerBuffer hsiPwroffFlagBuffer(A_10C_HSI_PWROFF_FLAG, [](unsigned int newValue) {
  hsiCurrentPowerOff = newValue ? true : false;
  drawHsi();
});
/*
// Range counter
int hsiRangeCounter1 = 0;
int hsiRangeCounter10 = 0;
int hsiRangeCounter100 = 0;
int hsiRangeCounter1000 = 0;
DcsBios::IntegerBuffer hsiRcDBuffer(A_10C_HSI_RC_D, [](unsigned int newValue) {
  hsiRangeCounter1 = round(map(newValue, 0, 65535, 0, 100) / 10);
  hsiRangeCounter = hsiRangeCounter1 + hsiRangeCounter10 + hsiRangeCounter100 + hsiRangeCounter1000;
  drawHsi();
});
DcsBios::IntegerBuffer hsiRcCBuffer(A_10C_HSI_RC_C, [](unsigned int newValue) {
  hsiRangeCounter10 = round(map(newValue, 0, 65535, 0, 100) / 10) * 10;
  hsiRangeCounter = hsiRangeCounter1 + hsiRangeCounter10 + hsiRangeCounter100 + hsiRangeCounter1000;
  drawHsi();
});
DcsBios::IntegerBuffer hsiRcBBuffer(A_10C_HSI_RC_B, [](unsigned int newValue) {
  hsiRangeCounter100 = round(map(newValue, 0, 65535, 0, 100) / 10) * 100;
  hsiRangeCounter = hsiRangeCounter1 + hsiRangeCounter10 + hsiRangeCounter100 + hsiRangeCounter1000;
  drawHsi();
});
DcsBios::IntegerBuffer hsiRcABuffer(A_10C_HSI_RC_A, [](unsigned int newValue) {
  hsiRangeCounter1000 = round(map(newValue, 0, 65535, 0, 100) / 10) * 1000;
  hsiRangeCounter = hsiRangeCounter1 + hsiRangeCounter10 + hsiRangeCounter100 + hsiRangeCounter1000;
  drawHsi();
});
*/
void setup() {
  setup1_Hsi();

  tft.init();

  tft.fillScreen(TFT_BLACK);
  tft.setRotation(2);
  tft.setSwapBytes(true);

  initScreen_Hsi();

  DcsBios::setup();

  drawHsi();
}

void loop() {
  DcsBios::loop();
}
