// Load TFT driver library
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft;           // A single instance is used for all displays

#include "hsi.h"

void setup() {
  // Serial.begin(115200);
  setup1_Hsi();

  tft.init();

  tft.fillScreen(TFT_BLACK);
  // tft.setTextColor(TFT_WHITE);
  tft.setRotation(2);
  tft.setSwapBytes(true);

  initScreen_Hsi();
  
  // tft.setPivot(120, 120);
}

int angleHeading = 0;
int angleBearing1 = 0;
int angleBearing2 = 0;
int angleCourseArrow = 0;

void loop() {

  drawHsi(angleHeading, angleBearing1, angleBearing2, angleCourseArrow);

  angleHeading++;
  angleBearing1 += 2;
  angleBearing2--;
  angleCourseArrow -= 2;
}
