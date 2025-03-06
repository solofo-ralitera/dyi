#ifndef Engine_h
#define Engine_h

#include "Arduino.h"
#include <TFT_eSPI.h>

#define ENGINE_GAUGE_CENTER 120, 120, 120, 115
#define ENGINE_GAUGE_START_ANGLE 25
#define ENGINE_GAUGE_END_ANGLE 245

#define ENGINE_MAX_OIL_PRESSURE 100
#define ENGINE_MAX_CORE_SPEED 100
#define ENGINE_MAX_FAN_SPEED 100
#define ENGINE_MAX_ITT 110 // * CX 100
#define ENGINE_MAX_FUEL_FLOW 50 // * 100 ppm
#define ENGINE_MAX_HYD_PRESSURE 4000

int E_ANGLE_100 = ENGINE_GAUGE_END_ANGLE - ENGINE_GAUGE_START_ANGLE; // 200

class Engine
{
  public:
    Engine(TFT_eSPI *_tft, TFT_eSprite *_spr, TFT_eSprite *_sprValue,int _pin) {
      tft = _tft;
      spr = _spr;
      sprValue = _sprValue;
      pin = _pin;
    };

    void init() {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    };

    void initScreen() {
      digitalWrite(pin, HIGH);
      
      // Init sprite here
      spr->setColorDepth(8);
      spr->createSprite(7, 25);
      spr->setSwapBytes(true);
      spr->setPivot(3, 112);

      sprValue->setColorDepth(8);
      sprValue->createSprite(80, 60);
      sprValue->setSwapBytes(true);
      
      digitalWrite(pin, HIGH);
    };

    bool isDrawing = false;
    void drawScreen() {
      if (!currentVisibility) return;
      if (isDrawing) return;
      
      isDrawing = true;
      // digitalWrite(pin, HIGH);
      digitalWrite(pin, LOW);

      tft->fillScreen(TFT_BLACK);
      switch (currentDisplay) {
        case 0: oilPressureGauge(); break;
        case 1: coreSpeedGauge(); break;
        case 2: fanSpeedGauge(); break;
        case 3: ittGauge(); break;
        case 4: fuelFlowGauge(); break;
        default:
        break;
      }

      digitalWrite(pin, HIGH);

      updateEngine();
      isDrawing = false;
    };

    // Change gauge display
      // 0: Oil Pressure (PSI)
      // 1: Engine Core Speed (% RPM)
      // 2: Fan Speed (% RPM)
      // 3: Interstage Turbine Temp (ITT) (°C*100)
      // 4: Fuel Flow (Pounds Per Hour)
    void changeDisplay(int d) {
      if (d >= 0 && d <= 4) {
        currentDisplay = d;
        drawScreen();
      }
    };

    void drawGaugesList() {
      tft->setTextSize(1);

      // Remove selected indicator
      tft->setTextColor(TFT_BLACK);
      tft->drawString("->", 125, 80, 2);
      tft->drawString("->", 125, 100, 2);
      tft->drawString("->", 125, 120, 2);
      tft->drawString("->", 125, 140, 2);
      tft->drawString("->", 125, 160, 2);

      // Selected indicator
      tft->setTextColor(oilPressureColor);
      if (currentDisplay == 0) tft->drawString("->", 125, 80, 2);
      tft->drawString("OIL PRESS", 150, 80, 2);

      tft->setTextColor(coreSpeedColor);
      if (currentDisplay == 1) tft->drawString("->", 125, 100, 2);
      tft->drawString("CORE % RPM", 150, 100, 2);

      tft->setTextColor(fanSpeedColor);
      if (currentDisplay == 2) tft->drawString("->", 125, 120, 2);
      tft->drawString("FAN % RPM", 150, 120, 2);

      tft->setTextColor(ittColor);
      if (currentDisplay == 3) tft->drawString("->", 125, 140, 2);
      tft->drawString("ITT TEMP", 150, 140, 2);

      tft->setTextColor(fuelFlowColor);
      if (currentDisplay == 4) tft->drawString("->", 125, 160, 2);
      tft->drawString("FUEL FLOW", 150, 160, 2);

      tft->setTextColor(TFT_WHITE, TFT_BLACK);
    }
    
    int hydPressure = 0;
    void setHydPressure(unsigned int biosValue) {
      hydPressure = map(biosValue, 0, 65535, 0, ENGINE_MAX_HYD_PRESSURE);
      updateEngine();
    };
    void drawHydPress() {
      // Hys Press
      if (hydPressure < 2800) tft->setTextColor(TFT_LIGHTGREY, TFT_RED);
      else if (hydPressure >= 2800 && hydPressure <= 3500) tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
      else tft->setTextColor(TFT_LIGHTGREY, TFT_ORANGE);
      
      tft->setTextSize(1);
      tft->drawString(" HYD ", 115, 225, 2);
      
      tft->setTextColor(TFT_WHITE, TFT_BLACK);
      tft->setTextSize(1);
    }

    void updateEngine() {
      switch (currentDisplay) {
        case 0: updateEngine(currentOilPressureBiosValue); break;
        case 1: updateEngine(currentCoreSpeedBiosValue); break;
        case 2: updateEngine(currentFanSpeedBiosValue); break;
        case 3: updateEngine(currentITTBiosValue); break;
        case 4: updateEngine(currentFuelFlowBiosValue); break;
        default:
        break;
      }
    }

    void updateEngine(int biosValue) {
      if (!currentVisibility) return;

      // draw each xx millis
      currentTimestamp = millis();
      // 10fps => 100ms
      if (currentTimestamp - lastTimestamp < 100) {
        return;
      }
      lastTimestamp = currentTimestamp;

      int angle = map(biosValue, 0, 65535, ENGINE_GAUGE_START_ANGLE, ENGINE_GAUGE_END_ANGLE) - 180;

      digitalWrite(pin, LOW);

      // Clear old sprite
      spr->fillSprite(TFT_BLACK);
      spr->pushRotated(currentAngle);

      drawGaugesList();
      drawHydPress();

      currentAngle = angle;
      // Draw pin
      spr->drawWedgeLine(3, 0, 3, 25, 1, 7, TFT_DARKGREY, TFT_LIGHTGREY);
      spr->pushRotated(currentAngle, TFT_BLACK);

      // Draw value
      sprValue->fillSprite(TFT_BLACK);

      sprValue->setTextColor(getCurrentColor());
      sprValue->setTextSize(3);
      sprValue->drawNumber(getCurrentValue(), 5, 0, 2);
      sprValue->setTextSize(1);
      // Draw current unit
      switch (currentDisplay) {
        // Oil pressure
        case 0: sprValue->drawString("P.S.I.   ", 5, 45, 2); break;
        // Engine core speed
        case 1: sprValue->drawString("% RPM    ", 5, 45, 2); break;
        // Fan speed
        case 2: sprValue->drawString("% RPM    ", 5, 45, 2); break;
        // ITT
        case 3: sprValue->drawString("C x 100", 5, 45, 2); break;
        // Fuel flow
        case 4: sprValue->drawString("PPH x 100", 5, 45, 2); break;
        default: break;
      }

      sprValue->pushSprite(40, 90);

      digitalWrite(pin, HIGH);
    };

    uint32_t getCurrentColor() {
      switch (currentDisplay) {
        case 0: return oilPressureColor;
        case 1: return coreSpeedColor;
        case 2: return fanSpeedColor;
        case 3: return ittColor;
        case 4: return fuelFlowColor;
        default: return TFT_LIGHTGREY;
      }
    }

    int getCurrentValue() {
      switch (currentDisplay) {
        case 0: return oilPressure;
        case 1: return coreSpeed;
        case 2: return fanSpeed;
        case 3: return itt;
        case 4: return fuelFlow;
        default: return 0;
      }
    }
    
    int oilPressure = 0;
    uint32_t oilPressureColor = TFT_LIGHTGREY;
    void setOilPressure(unsigned int biosValue) {
      currentOilPressureBiosValue = biosValue;
      oilPressure = map(biosValue, 0, 65535, 0, ENGINE_MAX_OIL_PRESSURE);

      if (oilPressure < 40) oilPressureColor = TFT_RED;
      // else if (oilPressure >= 30 && oilPressure < 40) oilPressureColor = TFT_RED;
      else if (oilPressure >= 40 && oilPressure < 55) oilPressureColor = TFT_YELLOW;
      else if (oilPressure >= 55 && oilPressure <= 95) oilPressureColor = TFT_DARKGREEN;
      // else if (oilPressure > 85 && oilPressure <= 95) oilPressureColor = TFT_ORANGE;
      else oilPressureColor = TFT_RED;

      if (currentDisplay == 0) updateEngine(biosValue);
    };

    int coreSpeed = 0;
    uint32_t coreSpeedColor = TFT_LIGHTGREY;
    void setCoreSpeed(unsigned int biosValue) {
      currentCoreSpeedBiosValue = biosValue;
      coreSpeed = map(biosValue, 0, 65535, 0, ENGINE_MAX_CORE_SPEED);

      if (coreSpeed < 56) coreSpeedColor = TFT_LIGHTGREY;
      else if (coreSpeed >= 56 && coreSpeed <= 92) coreSpeedColor = TFT_DARKGREEN;
      else if (coreSpeed > 92 && coreSpeed <= 98) coreSpeedColor = TFT_ORANGE;
      else coreSpeedColor = TFT_RED;

      if (currentDisplay == 1) updateEngine(biosValue);
    };

    // !!! Gauge non linéraire
    int fanSpeed = 0;
    uint32_t fanSpeedColor = TFT_LIGHTGREY;
    void setFanSpeed(unsigned int biosValue) {
      currentFanSpeedBiosValue = biosValue;
      if (biosValue <= 24358) {
        // <= 75% RPM (gauge par pas de 5%)
        fanSpeed = map(biosValue, 0, 24358, 0, 75);
        biosValue *= 2.083;
      } else {
        // > 75% RPM (gauge par pas de 1%)
        fanSpeed = map(biosValue, 24358, 65535, 75, ENGINE_MAX_FAN_SPEED);
        biosValue = 26380 + biosValue;
      }
      // fanSpeed = map(biosValue, 0, 65535, 0, ENGINE_MAX_FAN_SPEED);

      if (fanSpeed < 25) fanSpeedColor = TFT_LIGHTGREY;
      else if (fanSpeed >= 25 && fanSpeed <= 95) fanSpeedColor = TFT_DARKGREEN;
      else if (fanSpeed > 95 && fanSpeed <= 100) fanSpeedColor = TFT_ORANGE;
      else fanSpeedColor = TFT_RED; 

      if (currentDisplay == 2) updateEngine(biosValue);
    }    

    //// !!! ne commence pas par 0
    int itt = 0;
    uint32_t ittColor = TFT_LIGHTGREY;
    void setItt(unsigned int biosValue) {
      currentITTBiosValue = biosValue;
      itt = map(biosValue, 0, 65535, 10, ENGINE_MAX_ITT) + 4; // + 4 Ajustemement du début à 10

      if (itt < 27.5) ittColor = TFT_LIGHTGREY;
      else if (itt >= 27.5 && itt <= 86.5) ittColor = TFT_DARKGREEN;
      else ittColor = TFT_RED;

      if (currentDisplay == 3) updateEngine(biosValue);
    }
    
    int fuelFlow = 0;
    uint32_t fuelFlowColor = TFT_LIGHTGREY;
    void setFuelFlow(unsigned int biosValue) {
      currentFuelFlowBiosValue = biosValue;
      fuelFlow = map(biosValue, 0, 65535, 0, ENGINE_MAX_FUEL_FLOW);

      if (fuelFlow < 3) fuelFlowColor = TFT_RED;
      else if (fuelFlow >= 3 && fuelFlow <= 15) fuelFlowColor = TFT_LIGHTGREY;
      else if (fuelFlow > 15 && fuelFlow <= 41) fuelFlowColor = TFT_DARKGREEN;
      else fuelFlowColor = TFT_ORANGE;

      if (currentDisplay == 4) updateEngine(biosValue);
    }

    // 0: Oil Pressure (PSI)
      //  < 30 White
      //  [30-40] Red
      //  [40-55] Yellow
      //  [55-85] Green
      //  [85-95] Orange
      //  > 95 Red
    void oilPressureGauge() {
      // < 30 psi Red / White
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER, 
        ENGINE_GAUGE_START_ANGLE,
        ENGINE_GAUGE_START_ANGLE + (30 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        TFT_LIGHTGREY, TFT_LIGHTGREY, false);
      //  [30-40] Red
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (30 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        ENGINE_GAUGE_START_ANGLE + (40 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        TFT_RED, TFT_RED, false);
      //  [40-55] Yellow
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (40 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        ENGINE_GAUGE_START_ANGLE + (55 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        TFT_YELLOW, TFT_YELLOW, false);
      // [55-85] Green
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (55 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        ENGINE_GAUGE_START_ANGLE + (95 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        TFT_DARKGREEN, TFT_DARKGREEN, false);
      /*
      // [85-95] Orange
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (85 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        ENGINE_GAUGE_START_ANGLE + (95 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        TFT_ORANGE, TFT_ORANGE, false);
      */
      // > 95 Red
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (95 * E_ANGLE_100 / ENGINE_MAX_OIL_PRESSURE),
        ENGINE_GAUGE_END_ANGLE,
        TFT_RED, TFT_RED, false);
    };

    //  1: Engine Core Speed (% RPM)
      //  < 56 Red / White
      //  [56-92] Green
      //  [92-98] Orange
      //  > 98 Red
    void coreSpeedGauge() {
      //  < 56 Red / White
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER, 
        ENGINE_GAUGE_START_ANGLE,
        ENGINE_GAUGE_START_ANGLE + (56 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        TFT_LIGHTGREY, TFT_LIGHTGREY, false);
      //  [56-90] Green
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (56 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        ENGINE_GAUGE_START_ANGLE + (92 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        TFT_DARKGREEN, TFT_DARKGREEN, false);        
      //  [90-98] Orange
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (92 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        ENGINE_GAUGE_START_ANGLE + (98 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        TFT_ORANGE, TFT_ORANGE, false);        
      //  > 98 Red
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (98 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        ENGINE_GAUGE_END_ANGLE, // ENGINE_GAUGE_START_ANGLE + (102 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        TFT_RED, TFT_RED, false);        
      /*
      // > 102 Red
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (102 * E_ANGLE_100 / ENGINE_MAX_CORE_SPEED),
        ENGINE_GAUGE_END_ANGLE,
        TFT_RED, TFT_RED, false);*/
    };

    //  2: Fan Speed (% RPM)
    // TODO !!! non linéaire
      //  < 25 Red / White
      //  [25-95] Green (82% at takeoff)
      //  [95-100] Orange
      //  > 100 Red
    void fanSpeedGauge() {
      //  < 25 White
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER, 
        ENGINE_GAUGE_START_ANGLE,
        ENGINE_GAUGE_START_ANGLE + (25 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        TFT_LIGHTGREY, TFT_LIGHTGREY, false);
      //  [25-95]
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (25 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        ENGINE_GAUGE_START_ANGLE + (95 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        TFT_DARKGREEN, TFT_DARKGREEN, false);   
      //  [95-100] Orange
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (95 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        ENGINE_GAUGE_END_ANGLE, // ENGINE_GAUGE_START_ANGLE + (100 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        TFT_ORANGE, TFT_ORANGE, false);     
      // 82 Takeoff
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (81 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        ENGINE_GAUGE_START_ANGLE + (82 * E_ANGLE_100 / ENGINE_MAX_FAN_SPEED),
        TFT_BLUE, TFT_BLUE, false);
    };

    //  3: Interstage Turbine Temp (ITT) (°C*100)
      //  < 275 White
      //  [275-865] Green
      //  > 865 Red
    void ittGauge() {
      //  < 275 White
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER, 
        ENGINE_GAUGE_START_ANGLE,
        ENGINE_GAUGE_START_ANGLE + (27.5 * E_ANGLE_100 / ENGINE_MAX_ITT),
        TFT_LIGHTGREY, TFT_LIGHTGREY, false);
      //  [275-865] Green
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (27.5 * E_ANGLE_100 / ENGINE_MAX_ITT),
        ENGINE_GAUGE_START_ANGLE + (86.5 * E_ANGLE_100 / ENGINE_MAX_ITT),
        TFT_DARKGREEN, TFT_DARKGREEN, false);
      //  > 865 Red
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (86.5 * E_ANGLE_100 / ENGINE_MAX_ITT),
        ENGINE_GAUGE_END_ANGLE, // ENGINE_GAUGE_START_ANGLE + (110 * E_ANGLE_100 / ENGINE_MAX_ITT),
        TFT_RED, TFT_RED, false);
      // 900 startup
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (89.9 * E_ANGLE_100 / ENGINE_MAX_ITT),
        ENGINE_GAUGE_START_ANGLE + (90 * E_ANGLE_100 / ENGINE_MAX_ITT),
        TFT_BLUE, TFT_BLUE, false);        
    };

    //  4: Fuel Flow (Pounds Per Hour)
      //  [300-1500] White
      //  [1500-4100] Green
      //  > 4100 Orange
    void fuelFlowGauge() {
      //  < 1500 White
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER, 
        ENGINE_GAUGE_START_ANGLE,
        ENGINE_GAUGE_START_ANGLE + (3 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        TFT_RED, TFT_RED, false);
      //  [300-1500] Green
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (3 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        ENGINE_GAUGE_START_ANGLE + (15 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        TFT_LIGHTGREY, TFT_LIGHTGREY, false);
      //  [1500-4100] Green
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (15 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        ENGINE_GAUGE_START_ANGLE + (41 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        TFT_DARKGREEN, TFT_DARKGREEN, false);
      //  > 4100 Orange
      tft->drawSmoothArc(ENGINE_GAUGE_CENTER,
        ENGINE_GAUGE_START_ANGLE + (41 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        ENGINE_GAUGE_END_ANGLE, // ENGINE_GAUGE_START_ANGLE + (50 * E_ANGLE_100 / ENGINE_MAX_FUEL_FLOW),
        TFT_ORANGE, TFT_ORANGE, false);
    };

    void toggleDisplay() {
      currentVisibility = !currentVisibility;
      if (currentVisibility) {
        drawScreen();
      } else {
        digitalWrite(pin, LOW);
        tft->fillScreen(TFT_BLACK);
        digitalWrite(pin, HIGH);
      }
    };
  private:
    TFT_eSPI* tft;
    TFT_eSprite* spr;
    TFT_eSprite* sprValue;

    int pin = 0;
    /**
    0: Oil Pressure (PSI)
    1: Engine Core Speed (% RPM)
    2: Fan Speed (% RPM)
    3: Interstage Turbine Temp (ITT) (°C*100)
    4: Fuel Flow (Pounds Per Hour)
    */
    int currentDisplay = 0;

    int currentAngle = 0;
    unsigned long currentTimestamp = millis();
    unsigned long lastTimestamp = 0;
    unsigned int currentOilPressureBiosValue = 0;
    unsigned int currentCoreSpeedBiosValue = 0;
    unsigned int currentFanSpeedBiosValue = 0;
    unsigned int currentITTBiosValue = 0;
    unsigned int currentFuelFlowBiosValue = 0;
    bool currentVisibility = false;
};

#endif
