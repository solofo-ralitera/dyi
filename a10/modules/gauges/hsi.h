#ifndef hsi_h
#define hsi_h

#include <TFT_eSPI.h>
#include "hsi_heading_background.h"

#define TFT_CS_HSI 15

#define HSI_RADIUS 100
#define HSI_TEXT_OFFSET 10

// Wiring
// https://www.youtube.com/watch?v=pmCc7z_Mi8I&t=2s&ab_channel=TheLastOutpostWorkshop
// Rotate sprite
// https://www.youtube.com/watch?v=oqBa_ptBmLU&ab_channel=VolosProjects
// Image to byte array
// http://www.rinkydinkelectronics.com/t_imageconverter565.php

TFT_eSprite sprHsi = TFT_eSprite(&tft);
TFT_eSprite sprHsiHeading = TFT_eSprite(&tft);

TFT_eSprite sprHsiBearing1 = TFT_eSprite(&tft);
TFT_eSprite sprHsiBearing2 = TFT_eSprite(&tft);
TFT_eSprite sprHsiCourseArrow = TFT_eSprite(&tft);

void setup1_Hsi() {
  /*
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  */
  pinMode(TFT_CS_HSI, OUTPUT);
  digitalWrite(TFT_CS_HSI, LOW);

}

void initScreen_Hsi() {
  digitalWrite(TFT_CS_HSI, HIGH);


  sprHsi.setColorDepth(8);
  sprHsi.createSprite(240, 240);
  sprHsi.setSwapBytes(true);
  // sprHsi.setPivot(120, 120);

  sprHsiHeading.setColorDepth(8);
  sprHsiHeading.createSprite(200, 200);
  sprHsiHeading.setSwapBytes(true);
  sprHsiHeading.setPivot(100, 100);
  sprHsiHeading.fillSmoothCircle(100, 100, 100, TFT_BLACK);
  sprHsiHeading.pushImage(0, 0, 200, 200, hsi_heading_background);

  sprHsiBearing1.setColorDepth(8);
  sprHsiBearing1.createSprite(3, 20);
  sprHsiBearing1.setSwapBytes(true);
  sprHsiBearing1.fillSprite(TFT_DARKGREY);
  sprHsiBearing1.setPivot(2, 120);

  sprHsiBearing2.setColorDepth(8);
  sprHsiBearing2.createSprite(15, 8);
  sprHsiBearing2.setSwapBytes(true);
  sprHsiBearing2.fillSprite(TFT_DARKGREY);
  sprHsiBearing2.setPivot(8, 106);

  sprHsiCourseArrow.setColorDepth(8);
  sprHsiCourseArrow.createSprite(5, 150);
  sprHsiCourseArrow.setSwapBytes(true);
  sprHsiCourseArrow.setPivot(2, 79);
  sprHsiCourseArrow.drawWedgeLine(2, 0, 2, 20, 1, 5, TFT_WHITE);
  sprHsiCourseArrow.drawWedgeLine(2, 139, 2, 150, 5, 5, TFT_WHITE);
}


void drawPlane() {
  sprHsi.fillRect(119, 100, 4, 50, TFT_DARKGREY); // H line
  sprHsi.fillRect(100, 119, 40, 4, TFT_DARKGREY); // V line
  sprHsi.fillRect(110, 146, 20, 4, TFT_DARKGREY); // V tail

  // sprHsi.drawPixel(120, 120, TFT_WHITE);
}

void drawHeading(int angle) {
  sprHsiHeading.pushRotated(&sprHsi, angle, TFT_BLACK);
}

void drawBearing(int angle1, int angle2) {
  sprHsiBearing2.pushRotated(&sprHsi, angle2, TFT_BLACK);
  sprHsiBearing1.pushRotated(&sprHsi, angle1, TFT_BLACK);
}

void drawCourseArrow(int angle) {
  sprHsiCourseArrow.pushRotated(&sprHsi, angle, TFT_BLACK);
  sprHsi.drawNumber(angle >= 360 ? (angle - 360) : (angle < 0 ? 360 + angle : angle), 130, 130, 2);
}

void drawHsi(int angleHeading, int angleBearing1, int angleBearing2, int angleCourseArrow) {
  digitalWrite(TFT_CS_HSI, LOW);

  sprHsi.fillSprite(TFT_BLACK);

  drawHeading(angleHeading);
  drawPlane();
  drawBearing(angleBearing1, angleBearing2);
  drawCourseArrow(angleCourseArrow);

  sprHsi.pushSprite(0, 0);

  digitalWrite(TFT_CS_HSI, HIGH);
}

#endif