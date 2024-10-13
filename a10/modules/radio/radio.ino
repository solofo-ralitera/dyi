#include <Wire.h>

#include "PushButton.h"
#include "AutoReleaseSwitch.h"

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include "KnobJoy.h"

#include "radio.h"

// Adresse I2C du module
#define I2C_ADDRESS 5
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 1
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
};

#define BTN_MIC_SWITCH_DOWN 0
#define BTN_MIC_SWITCH_AFT 1
#define BTN_MIC_SWITCH_FWD 2

// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[4][2] = {
  {0, 0},{0, 1},{0, 2},{0, 3},
};

#include "Radios.h"
Radios radios;
unsigned long currentMillis = 0;

#include "arc210Cmd.h"
#include "uhfCmd.h"
#include "vhfFmCmd.h"
#include "vhfAmCmd.h"
#include "ilsCmd.h"
#include "tacanCmd.h"
#include "intercomPanel.h"
#include "electricalPowerPanel.h"
#include "checkListsCmd.h"

void setup(void) {
  pinMode(A15, INPUT_PULLUP);
  
  // Jusqu'a 50 beacause 51, 52 and 53 are used by ledMatrix
  for (int i = 22; i <= 50; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  radios.startScreenAndBios();
  initElectricalPowerPanel();

  Wire.begin(I2C_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Set the request event handler
}

void requestEvent()
{
  Wire.write(I2C_DATA, BUFFER_SIZE);
}

void loop(void) {
  currentMillis = millis();

  radios.run();
  runElectricalPowerPanel();
  
  // All push buttons
  int pbCode = getPBCode(analogRead(A15));

  // Mod selector Orange
  static KnobJoy modSelector(I2C_DATA, 27, 26);
  modSelector.runCallBack([]() {
    radios.activatePreviousModule();
  }, []() {
    radios.activateNextModule();
  });

  switch(radios.getActivatedModule()) {
    case 0:
      if (radios.isArc210Available()) {
        arc210Commands(pbCode);
      } else {
        vhfAmCommands(pbCode);
      }
      break;
    case 1:
      uhfCommands(pbCode); break;
    case 2:
      vhfFmCommands(pbCode); break;
    case 3:
      ilsCommands(pbCode); break;
    case 4:
      tacanCommands(pbCode); break;
    case 5:
      intercomPanelCommands(pbCode); break;
    case 6:
      checklistsCommands(pbCode); break;
  }
}
