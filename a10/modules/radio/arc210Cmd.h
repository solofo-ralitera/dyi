/*
Gestion des radios Arc10, Com, UHF, ILS, Tacan
*/
#ifndef arc210Cmd_h
#define arc210Cmd_h


#include "PushButton.h"
#include "KnobJoy.h"
#include "AutoReleaseSwitch.h"

void arc210PushButton(int pbCode) {
  static PushButton fskUpper(I2C_DATA, BUTTON_INDEX[BTN_ARC210_FSK_UPPER]);
  fskUpper.runCallBack(pbCode == PB_TOP_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_FSK_UP", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_FSK_UP", "0");
  });
  /*
  static PushButton fskMiddle(I2C_DATA, BUTTON_INDEX[BTN_ARC210_FSK_MIDDLE]);
  fskMiddle.run(pbCode == PB_MIDDLE_SCREEN ? 0 : 1);

  static PushButton fskLower(I2C_DATA, BUTTON_INDEX[PB_BOTTOM_SCREEN]);
  fskLower.run(pbCode == BTN_ARC210_FSK_LOWER ? 0 : 1);

  static PushButton micSwitchFwd(I2C_DATA, BUTTON_INDEX[BTN_ARC210_MIC_SWITCH_FWD]);
  micSwitchFwd.run(pbCode == PB_VOLUME ? 0 : 1);

  static PushButton amFm(I2C_DATA, BUTTON_INDEX[BTN_ARC210_AMFM]);
  amFm.run(pbCode == PB_AMFM ? 0 : 1);

  static PushButton menu(I2C_DATA, BUTTON_INDEX[BTN_ARC210_MENU]);
  menu.run(pbCode == PB_MENU ? 0 : 1);

  static PushButton offset(I2C_DATA, BUTTON_INDEX[BTN_ARC210_OFFSET]);
  offset.run(pbCode == PB_OFFSET ? 0 : 1);

  // Maron
  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_L_1],
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_R_1],
    &currentMillis
  );

  // Rouge
  static KnobJoy masterMode(I2C_DATA, 25, 24);
  static AutoReleaseSwitch masterModeOff(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_MASTER_MODE_OFF]);
  static AutoReleaseSwitch masterModeTRG(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_MASTER_MODE_TRG]);
  static AutoReleaseSwitch masterModeTR(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_MASTER_MODE_TR]);
  static AutoReleaseSwitch masterModeChgPrst(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_MASTER_MODE_CHG_PRST]);
  masterMode.runCallBack([]() {
      switch(radios.getArc210MasterMode()) {
        case 0: // OFF -> CHG PRST
          masterModeChgPrst.run(0, &currentMillis);
          break;
        case 1: // TR G -> OFF
          masterModeOff.run(0, &currentMillis);
          break;
        case 2: // TR -> TR G
          masterModeTRG.run(0, &currentMillis);
          break;
        case 3: // CHG PRST -> TR
          masterModeTR.run(0, &currentMillis);
          break;
        default:
          break;
      }
  }, []() {
      switch(radios.getArc210MasterMode()) {
        case 0: // OFF -> TR G
          masterModeTRG.run(0, &currentMillis);
          break;
        case 1: // TR G -> TR
          masterModeTR.run(0, &currentMillis);
          break;
        case 2: // TR -> CHG PRST
          masterModeChgPrst.run(0, &currentMillis);
          break;
        case 3: // CHG PRST -> OFF
          masterModeOff.run(0, &currentMillis);
          break;
        default:
          break;
      }
  });

  // Jaune
  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_L_2],
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_R_2],
    &currentMillis
  );

  // Vert
  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_L_3],
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_R_3],
    &currentMillis
  );

  // Bleu
  static KnobJoy channel(I2C_DATA, 33, 32);
  channel.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_CHANNEL_L],
    BUTTON_INDEX[BTN_ARC210_CHANNEL_R],
    &currentMillis
  );

  // Violet
  static KnobJoy freqSelector4(I2C_DATA, 35, 34);
  freqSelector4.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_L_4],
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_R_4],
    &currentMillis
  );

  // Gris
  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  static AutoReleaseSwitch secondaryModePrst(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_SECONDARY_MODE_PRST]);
  static AutoReleaseSwitch secondaryModeMan(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_SECONDARY_MODE_MAN]);
  static AutoReleaseSwitch secondaryMode243(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_SECONDARY_MODE_243]);
  static AutoReleaseSwitch secondaryMode121Pull(1, I2C_DATA, BUTTON_INDEX[BTN_ARC210_SECONDARY_MODE_121PULL]);
  secondaryMode.runCallBack([]() {
      switch(radios.getArc210MasterMode()) {
        case 0: // PRST -> 121 PULL
          secondaryMode121Pull.run(0, &currentMillis);
          break;
        case 1: // 121 PULL -> 243
          secondaryMode243.run(0, &currentMillis);
          break;
        case 2: // 243 -> MAN
          secondaryModeMan.run(0, &currentMillis);
          break;
        case 3: // MAN -> PRST
          secondaryModePrst.run(0, &currentMillis);
          break;
        default:
          break;
      }
  }, []() {
      switch(radios.getArc210SecondaryMode()) {
        case 0: // PRST -> MAN
          secondaryModeMan.run(0, &currentMillis);
          break;
        case 1: // MAN -> 243
          secondaryMode243.run(0, &currentMillis);
          break;
        case 2: // 243 -> 121 PULL
          secondaryMode121Pull.run(0, &currentMillis);
          break;
        case 3: // 121 PULL -> PRST
          secondaryModePrst.run(0, &currentMillis);
          break;
        default:
          break;
      }
  });

  // Blanc -> volume knob n/a

  // Noir
  static KnobJoy squelch(I2C_DATA, 41, 40);
  squelch.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_SQL_ON],
    BUTTON_INDEX[BTN_ARC210_SQL_OFF],
    &currentMillis
  );  

  // Marron
  static KnobJoy freqSelector5(I2C_DATA, 42, 43);
  freqSelector5.runIndefiniteLeftRight(
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_L_5],
    BUTTON_INDEX[BTN_ARC210_FREQUENCY_SELECTOR_R_5],
    &currentMillis
  );
  */
}
#endif

