#include <Wire.h>
#include "PushButton.h"
#include "AutoReleaseSwitch.h"

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include "KnobJoy.h"

#include "radio.h"

// Adresse I2C du module
#define I2C_ADDRESS 5
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 7
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

#define BTN_ARC210_FSK_UPPER 0
#define BTN_ARC210_FSK_MIDDLE 1
#define BTN_ARC210_FSK_LOWER 2
#define BTN_ARC210_FREQUENCY_SELECTOR_L_1 3
#define BTN_ARC210_FREQUENCY_SELECTOR_R_1 4
#define BTN_ARC210_FREQUENCY_SELECTOR_L_2 5
#define BTN_ARC210_FREQUENCY_SELECTOR_R_2 6
#define BTN_ARC210_FREQUENCY_SELECTOR_L_3 7
#define BTN_ARC210_FREQUENCY_SELECTOR_R_3 8
#define BTN_ARC210_FREQUENCY_SELECTOR_L_4 9
#define BTN_ARC210_FREQUENCY_SELECTOR_R_4 10
#define BTN_ARC210_FREQUENCY_SELECTOR_L_5 11
#define BTN_ARC210_FREQUENCY_SELECTOR_R_5 12
#define BTN_ARC210_MASTER_MODE_OFF 13
#define BTN_ARC210_MASTER_MODE_TRG 14
#define BTN_ARC210_MASTER_MODE_TR 15
#define BTN_ARC210_MASTER_MODE_CHG_PRST 16
#define BTN_ARC210_SECONDARY_MODE_PRST 17
#define BTN_ARC210_SECONDARY_MODE_MAN 18
#define BTN_ARC210_SECONDARY_MODE_243 19
#define BTN_ARC210_SECONDARY_MODE_121PULL 20
#define BTN_ARC210_CHANNEL_L 21
#define BTN_ARC210_CHANNEL_R 22
#define BTN_ARC210_MENU 23
#define BTN_ARC210_AMFM 24
#define BTN_ARC210_OFFSET 25
#define BTN_ARC210_MIC_SWITCH_FWD 26
#define BTN_ARC210_SQL_ON 27
#define BTN_ARC210_SQL_OFF 28

#define BTN_UHF_FREQUENCY_SELECTOR_1_A 29 //
#define BTN_UHF_FREQUENCY_SELECTOR_1_3 30 // 
#define BTN_UHF_FREQUENCY_SELECTOR_1_2 31 //
#define BTN_UHF_FREQUENCY_SELECTOR_L_2 32
#define BTN_UHF_FREQUENCY_SELECTOR_R_2 33
#define BTN_UHF_FREQUENCY_SELECTOR_L_3 34
#define BTN_UHF_FREQUENCY_SELECTOR_R_3 35
#define BTN_UHF_FREQUENCY_SELECTOR_L_4 36
#define BTN_UHF_FREQUENCY_SELECTOR_R_4 37
#define BTN_UHF_FREQUENCY_SELECTOR_L_5 38
#define BTN_UHF_FREQUENCY_SELECTOR_R_5 39
#define BTN_UHF_VOLUME_L 40
#define BTN_UHF_VOLUME_R 41
#define BTN_UHF_LOAD 42
#define BTN_UHF_T_TONE 43
#define BTN_UHF_CHANNEL_L 44
#define BTN_UHF_CHANNEL_R 45
#define BTN_UHF_STATUS 46
#define BTN_UHF_SQL_ON 47
#define BTN_UHF_SECONDARY_MODE_MNL 48
#define BTN_UHF_SECONDARY_MODE_PRESET 49
#define BTN_UHF_SECONDARY_MODE_GRD 50
#define BTN_UHF_MASTER_MODE_OFF 51
#define BTN_UHF_MASTER_MODE_MAIN 52
#define BTN_UHF_MASTER_MODE_BOTH 53
#define BTN_UHF_MASTER_MODE_ADF 54
#define BTN_UHF_TEST_DISPLAY 55


// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[48][2] = {
  {0, 0},{0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7},
  {1, 0},{1, 1},{1, 2},{1, 3},{1, 4},{1, 5},{1, 6},{1, 7},
  {2, 0},{2, 1},{2, 2},{2, 3},{2, 4},{2, 5},{2, 6},{2, 7},
  {3, 0},{3, 1},{3, 2},{3, 3},{3, 4},{3, 5},{3, 6},{3, 7},
  {4, 0},{4, 1},{4, 2},{4, 3},{4, 4},{4, 5},{4, 6},{4, 7},
  {5, 0},{5, 1},{5, 2},{5, 3},{5, 4},{5, 5},{5, 6},{5, 7},
};

#include "Radios.h"
Radios radios;
unsigned long currentMillis = 0;

#include "arc210Cmd.h"
#include "uhfCmd.h"
#include "vhfFmCmd.h"
#include "ilsCmd.h"
#include "tacanCmd.h"

void setup(void) {
  // No serial available for Prod,
  //  !!! Set DCSBIOS_IRQ_SERIAL in Arc210
  // Serial.begin(9600);

  pinMode(A15, INPUT_PULLUP);
  for (int i = 22; i <= 53; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  radios.startScreenAndBios();

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

  // All push buttons
  int pbCode = getPBCode(analogRead(A15));

  // Mod selector Orange
  static KnobJoy modSelector(I2C_DATA, 27, 26);
  modSelector.runCallBack([]() {
    radios.activatePreviousModule();
  }, []() {
    radios.activateNextModule();
  });

  // Arc 210, VHF AM/FM
  if (radios.getActivatedModule() == 0) {
    arc210Commands(pbCode);
  }
  // UHF
  else if (radios.getActivatedModule() == 1) {
    uhfCommands(pbCode);
  }
  // VHF FM
  else if (radios.getActivatedModule() == 2) {
    vhfFmCommands(pbCode);
  }
  // ILS
  else if (radios.getActivatedModule() == 3) {
    ilsCommands(pbCode);
  }
  // TACAN
  else if (radios.getActivatedModule() == 4) {
    tacanCommands(pbCode);
  }
}