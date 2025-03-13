// #define DCSBIOS_IRQ_SERIAL
#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_DISABLE_SERVO
#include "DcsBios.h"

#include "PushButton.h"
#include "KnobJoyEsp32.h"

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
Engine engineR(&tft, &sprEngineR, &sprEngineValueR, 12); 
Engine engineL(&tft, &sprEngineL, &sprEngineValueL, 14); 

bool updateHsi = false;
bool updateEngineR = false;
bool updateEngineL = false;

void sendDcsCommand(const char* msg, const char* args) {
  while(!DcsBios::tryToSendDcsBiosMessage(msg, args));
}

DcsBios::IntegerBuffer hsiHdgBuffer(A_10C_HSI_HDG, [](unsigned int newValue) {
  hsiCurrentAngleHeading = map(newValue, 65535, 0, 359, 1);
  updateHsi = true;
  // drawHsi();
});

DcsBios::IntegerBuffer hsiBearing1Buffer(A_10C_HSI_BEARING1, [](unsigned int newValue) {
  hsiCurrentAngleBearing1 = map(newValue, 65535, 0, 359, 1);
  updateHsi = true;
  // drawHsi();
});

DcsBios::IntegerBuffer hsiBearing2Buffer(A_10C_HSI_BEARING2, [](unsigned int newValue) {
  hsiCurrentAngleBearing2 = map(newValue, 65535, 0, 359, 1);
  updateHsi = true;
  // drawHsi();
});

float hsiCourse1 = 0;
float hsiCourse10 = 0;
// Course unité
DcsBios::IntegerBuffer hsiCcBBuffer(A_10C_HSI_CC_B, [](unsigned int newValue) {
  hsiCourse1 = map(newValue, 65535, 0, 100, 0) / 10;
  hsiCurrentAngleCourseArrow = hsiCourse1 + (hsiCourse10 * 10);
  updateHsi = true;
  // drawHsi();
});
// Course dizaine
DcsBios::IntegerBuffer hsiCcABuffer(A_10C_HSI_CC_A, [](unsigned int newValue) {
  hsiCourse10 = map(newValue, 65535, 0, 360, 0) / 10;
  hsiCurrentAngleCourseArrow = hsiCourse1 + (hsiCourse10 * 10);
  updateHsi = true;
  // drawHsi();
});

DcsBios::IntegerBuffer hsiDeviationBuffer(A_10C_HSI_DEVIATION, [](unsigned int newValue) {
  hsiCurrentDeviation = map(newValue, 0, 65535, 55, -55);
  updateHsi = true;
  // drawHsi();
});

DcsBios::IntegerBuffer hsiBearingFlagBuffer(A_10C_HSI_BEARING_FLAG, [](unsigned int newValue) {
  hsiCurrentBearingFlag = newValue ? true : false;
  updateHsi = true;
  // drawHsi();
});

DcsBios::IntegerBuffer hsiPwroffFlagBuffer(A_10C_HSI_PWROFF_FLAG, [](unsigned int newValue) {
  hsiCurrentPowerOff = newValue ? true : false;
  updateHsi = true;
  // drawHsi();
});

//// Engine GAUGES
//    Core speed
DcsBios::IntegerBuffer lEngCoreBuffer(A_10C_L_ENG_CORE, [](unsigned int newValue) {
  engineL.setCoreSpeed(newValue);
});
DcsBios::IntegerBuffer rEngCoreBuffer(A_10C_R_ENG_CORE, [](unsigned int newValue) {
  engineR.setCoreSpeed(newValue);
});
//    Fan speed
DcsBios::IntegerBuffer lEngFanBuffer(A_10C_L_ENG_FAN, [](unsigned int newValue) {
  engineL.setFanSpeed(newValue);
});
DcsBios::IntegerBuffer rEngFanBuffer(A_10C_R_ENG_FAN, [](unsigned int newValue) {
  engineR.setFanSpeed(newValue);
});
//  Fuel flow
DcsBios::IntegerBuffer lEngFuelFlowBuffer(A_10C_L_ENG_FUEL_FLOW, [](unsigned int newValue) {
  engineL.setFuelFlow(newValue);
});
DcsBios::IntegerBuffer rEngFuelFlowBuffer(A_10C_R_ENG_FUEL_FLOW, [](unsigned int newValue) {
  engineR.setFuelFlow(newValue);
});
//  ITT
DcsBios::IntegerBuffer lEngTempBuffer(A_10C_L_ENG_TEMP, [](unsigned int newValue) {
  engineL.setItt(newValue);
});
DcsBios::IntegerBuffer rEngTempBuffer(A_10C_R_ENG_TEMP, [](unsigned int newValue) {
  engineR.setItt(newValue);
});
// Oil press
DcsBios::IntegerBuffer lOilPressBuffer(A_10C_L_OIL_PRESS, [](unsigned int newValue) {
  engineL.setOilPressure(newValue);
});
DcsBios::IntegerBuffer rOilPressBuffer(A_10C_R_OIL_PRESS, [](unsigned int newValue) {
  engineR.setOilPressure(newValue);
});
// Hyd Pressure
DcsBios::IntegerBuffer lHydPressBuffer(A_10C_L_HYD_PRESS, [](unsigned int newValue) {
  engineL.setHydPressure(newValue);
});
DcsBios::IntegerBuffer rHydPressBuffer(A_10C_R_HYD_PRESS, [](unsigned int newValue) {
  engineR.setHydPressure(newValue);
});

// Led gun & steering
DcsBios::LED gunReady(0x1026, 0x8000, 0);
/* DcsBios::IntegerBuffer gunReadyBuffer(A_10C_GUN_READY, [](unsigned int newValue) {
    digitalWrite(0, newValue ? HIGH : LOW);
}); */
DcsBios::LED nosewheelSteering(0x10da,0x0001, 5);
/* DcsBios::IntegerBuffer nosewheelSteeringBuffer(A_10C_NOSEWHEEL_STEERING, [](unsigned int newValue) {
    digitalWrite(5, newValue ? HIGH : LOW);
}); */

int currentDisplay = 2;

void setup() {
  // Hsi btn
  pinMode(26, INPUT_PULLUP);
  // Engine gauge btn
  pinMode(32, INPUT_PULLUP);

  // Gun ready & steering engaged
  pinMode(0, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(5, LOW);

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
  engineL.changeDisplay(currentDisplay);
  engineR.changeDisplay(currentDisplay);
}

void loop() {
  DcsBios::loop();

  if (updateHsi == true) {
    drawHsi();
    updateHsi = false;
  }

  static KnobJoyEsp32 engineCycle(35, 34);
  engineCycle.runCallBack([]() {
    currentDisplay++;
    if (currentDisplay >= 4) currentDisplay = 4;
    if (currentDisplay <= 0) currentDisplay = 0;

    engineL.changeDisplay(currentDisplay);
    engineR.changeDisplay(currentDisplay);
    delay(50);
  }, []() {
    currentDisplay--;
    if (currentDisplay >= 4) currentDisplay = 4;
    if (currentDisplay <= 0) currentDisplay = 0;

    engineL.changeDisplay(currentDisplay);
    engineR.changeDisplay(currentDisplay);
    delay(50);
  });

  static KnobJoyEsp32 hsiCourse(33, 25);
  hsiCourse.runCallBack([]() {
    sendDcsCommand("HSI_CRS_KNOB", "-1900");
     delay(50);
 }, []() {
    sendDcsCommand("HSI_CRS_KNOB", "+2100");
    delay(50);
  });

  static PushButton hsiBtn;
  hsiBtn.runCallBack(digitalRead(26) ? 0 : 1, []() {
    toggleHsi();
  });

  static PushButton engineGaugeBtn;
  engineGaugeBtn.runCallBack(digitalRead(32) ? 0 : 1, []() {
    engineR.toggleDisplay();
    engineL.toggleDisplay();
  });
}
