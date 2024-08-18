#include "LedControl.h"

LedControl ledMatrix = LedControl(51, 52, 53, 1);

void setup() {
    ledMatrix.shutdown(0, false);
    ledMatrix.setIntensity(0,8);
    ledMatrix.clearDisplay(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  ledMatrix.setLed(0, 6, 1, true);
  //ledMatrix.setLed(0, 6, 0, true);
  //ledMatrix.setLed(0, 7, 1, true);
  delay(1000);
  ledMatrix.setLed(0, 6, 1, false);
  //ledMatrix.setLed(0, 6, 0, false);
  //ledMatrix.setLed(0, 7, 1, false);
  delay(1000);
}

