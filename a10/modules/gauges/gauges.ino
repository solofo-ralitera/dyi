// #define DCSBIOS_IRQ_SERIAL
#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_DISABLE_SERVO
#include "DcsBios.h"

// Load TFT driver library
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft;           // A single instance is used for all displays

#include "hsi.h"

DcsBios::IntegerBuffer hsiHdgBuffer(A_10C_HSI_HDG, [](unsigned int newValue) {
  hsiCurrentAngleHeading = map(newValue, 65535, 0, 360, 1);
  drawHsi();
});

DcsBios::IntegerBuffer hsiBearing1Buffer(A_10C_HSI_BEARING1, [](unsigned int newValue) {
  hsiCurrentAngleBearing1 = map(newValue, 65535, 0, 360, 1);
  drawHsi();
});

DcsBios::IntegerBuffer hsiBearing2Buffer(A_10C_HSI_BEARING2, [](unsigned int newValue) {
  hsiCurrentAngleBearing2 = map(newValue, 65535, 0, 360, 1);
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
