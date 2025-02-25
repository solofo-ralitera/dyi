// #define DCSBIOS_IRQ_SERIAL
#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_DISABLE_SERVO
#include "DcsBios.h"

#include <math.h>

// Load TFT driver library
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft;           // A single instance is used for all displays
TFT_eSprite sprEngineR = TFT_eSprite(&tft);
TFT_eSprite sprEngineL = TFT_eSprite(&tft);
TFT_eSprite sprEngineValueR = TFT_eSprite(&tft);
TFT_eSprite sprEngineValueL = TFT_eSprite(&tft);

#include "hsi.h"
#include "engine.h"
Engine engineR(&tft, &sprEngineR, &sprEngineValueR, 22); 
Engine engineL(&tft, &sprEngineL, &sprEngineValueL, 21); 

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

//// Engine GAUGES


void setup() {
  setup1_Hsi();
  engineR.init();
  engineL.init();

  tft.init();

  tft.fillScreen(TFT_BLACK);
  tft.setRotation(2);
  tft.setSwapBytes(true);
  tft.setPivot(120, 120);
  tft.initDMA();

  initScreen_Hsi();
  engineR.initScreen();
  engineL.initScreen();

  DcsBios::setup();

  drawHsi();
  engineL.changeDisplay(2);
  engineR.changeDisplay(2);

}

// int current = 0;
// int currentDisplay = 0;
void loop() {
  DcsBios::loop();
  /*
  engineL.setOilPressure(current);
  engineR.setOilPressure(current);

  engineL.setCoreSpeed(current);
  engineR.setCoreSpeed(current);

  engineL.setFanSpeed(current);
  engineR.setFanSpeed(current);

  engineL.setItt(current);
  engineR.setItt(current);

  engineL.setFuelFlow(current);
  engineR.setFuelFlow(current);

  if (current > 65535) {
    current = 0;
    currentDisplay++;
    if (currentDisplay > 4) currentDisplay = 0;
    engineL.changeDisplay(currentDisplay);
    engineR.changeDisplay(currentDisplay);
  }
  current++;

  // delay(1);
  */
}
