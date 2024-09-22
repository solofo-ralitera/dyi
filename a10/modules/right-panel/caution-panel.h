#ifndef CautionPanel_h
#define CautionPanel_h

#include "LedControl.h"

LedControl cautionPanel = LedControl(51, 52, 53, 1);

void setupCautionPanel() {
  cautionPanel.shutdown(0, false);
  cautionPanel.setIntensity(0, 10);
  cautionPanel.clearDisplay(0);
}


#endif