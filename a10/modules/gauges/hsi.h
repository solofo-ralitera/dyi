#ifndef hsi_h
#define hsi_h

#include "Arduino.h"

#include <TFT_eSPI.h>
#include "hsi_heading_background.h"

#define TFT_CS_HSI 13
// HSI 19
// engine gauges R: 22, L: 21


#define HSI_RADIUS 100
#define HSI_TEXT_OFFSET 10

// Wiring
// https://www.youtube.com/watch?v=pmCc7z_Mi8I&t=2s&ab_channel=TheLastOutpostWorkshop
/**
VCC 3.3V
GND GND
DIN/SDA/MOSI 23
CLK/SCK/SCL 18
CS  15 one pin for each display
DC  2
RST 4 
*/
// or https://www.youtube.com/watch?v=k2c2zCmC_X0
// Rotate sprite
// https://www.youtube.com/watch?v=oqBa_ptBmLU&ab_channel=VolosProjects
// Image to byte array
// http://www.rinkydinkelectronics.com/t_imageconverter565.php
/**
TFT_eSPI
User_Setup: uncomment #define GC9A01_DRIVER
User_Setup_Select: uncomment #include <User_Setups/Setup46_GC9A01_ESP32.h>
*/


TFT_eSprite sprHsi = TFT_eSprite(&tft);
TFT_eSprite sprHsiHeading = TFT_eSprite(&tft);

TFT_eSprite sprHsiBearing1 = TFT_eSprite(&tft);
TFT_eSprite sprHsiBearing2 = TFT_eSprite(&tft);
TFT_eSprite sprHsiCourseArrow = TFT_eSprite(&tft);
TFT_eSprite sprHsiDeviation = TFT_eSprite(&tft);

unsigned long hsiCurrentTimestamp = millis();
unsigned long hsiLastTimestamp = 0;
int hsiCurrentAngleHeading = 0;
int hsiCurrentAngleBearing1 = 0;
int hsiCurrentAngleBearing2 = 0;
int hsiCurrentAngleCourseArrow = 0;
int hsiCurrentDeviation = 0; // [55-55]
bool hsiCurrentBearingFlag = true;
bool hsiCurrentPowerOff = true;
int hsiRangeCounter = 0; // [55-55]

bool hsiCurrentVisibility = false;

void setup1_Hsi() {
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
  // sprHsiHeading.fillSmoothCircle(100, 100, 100, TFT_BLACK);
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
  sprHsiBearing2.setPivot(8, 110);

  sprHsiCourseArrow.setColorDepth(8);
  sprHsiCourseArrow.createSprite(5, 150);
  sprHsiCourseArrow.setSwapBytes(true);
  sprHsiCourseArrow.setPivot(2, 79);
  sprHsiCourseArrow.drawWedgeLine(2, 0, 2, 20, 1, 5, TFT_DARKGREY);
  sprHsiCourseArrow.drawWedgeLine(2, 139, 2, 150, 5, 5, TFT_DARKGREY);

  sprHsiDeviation.setColorDepth(8);
  sprHsiDeviation.createSprite(5, 100);
  sprHsiDeviation.setSwapBytes(true);
  // sprHsiDeviation.setPivot(2, 79);
  sprHsiDeviation.fillSprite(TFT_DARKGREY);  

  digitalWrite(TFT_CS_HSI, HIGH);
}


void drawPlane() {
  sprHsi.fillRect(119, 100, 4, 50, TFT_DARKGREY); // H line
  sprHsi.fillRect(100, 119, 40, 4, TFT_DARKGREY); // V line
  sprHsi.fillRect(110, 146, 20, 4, TFT_DARKGREY); // V tail

  // Repère NSEW
  sprHsi.drawCircle(119, -1, 3, TFT_LIGHTGREY);
  sprHsi.drawCircle(119, 241, 3, TFT_LIGHTGREY);
  sprHsi.drawCircle(241, 119, 3, TFT_LIGHTGREY);
  sprHsi.drawCircle(-1, 119, 3, TFT_LIGHTGREY);
}

void drawHeading(int angle) {
  sprHsiHeading.pushRotated(&sprHsi, angle, TFT_BLACK);
}

void drawBearing(int angle1, int angle2) {
  sprHsiBearing2.pushRotated(&sprHsi, angle2, TFT_BLACK);
  sprHsiBearing1.pushRotated(&sprHsi, angle1, TFT_BLACK);
}

void drawCourseArrow(int angle) {
  if (hsiCurrentBearingFlag) {
    sprHsi.fillRect(110, 80, 20, 10, TFT_RED);
  }

  sprHsiCourseArrow.pushRotated(&sprHsi, hsiCurrentAngleHeading + angle, TFT_BLACK);
  // Deviation
  sprHsiDeviation.setPivot(hsiCurrentDeviation, 50);
  sprHsiDeviation.pushRotated(&sprHsi, hsiCurrentAngleHeading + angle, TFT_BLACK);
  
  sprHsi.drawNumber(angle, 150, 130, 2);
  // sprHsi.drawNumber(hsiRangeCounter, 60, 130, 2);  
}

void drawHsi() {
  // Toggle display is off
  if (!hsiCurrentVisibility) return;

  // draw each xx millis
  hsiCurrentTimestamp = millis();
  // 10fps => 100ms
  if (hsiCurrentTimestamp - hsiLastTimestamp < 50) {
    return;
  }
  hsiLastTimestamp = hsiCurrentTimestamp;

  digitalWrite(TFT_CS_HSI, LOW);

  sprHsi.fillSprite(TFT_BLACK);
  if (hsiCurrentPowerOff) {
    sprHsi.fillRect(200, 0, 40, 240, TFT_RED);
  }

  drawHeading(hsiCurrentAngleHeading);
  drawBearing(hsiCurrentAngleBearing1, hsiCurrentAngleBearing2);
  drawCourseArrow(hsiCurrentAngleCourseArrow);
  drawPlane();

  sprHsi.pushSprite(0, 0);

  digitalWrite(TFT_CS_HSI, HIGH);
}

void toggleHsi() {
  hsiCurrentVisibility = !hsiCurrentVisibility;
  if (hsiCurrentVisibility) {
    drawHsi();
  } else {
    digitalWrite(TFT_CS_HSI, LOW);
    tft.fillScreen(TFT_BLACK);
    digitalWrite(TFT_CS_HSI, HIGH);
  }
}

#endif