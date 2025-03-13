#ifndef checklistsCommands_h
#define checklistsCommands_h

#include "PushButton.h"
#include "KnobJoy.h"

/**
checkListPage
6 main menu
61 fuel
62 nvg
*/
int CheckListPage = 0;
void checklistsCommands(int pbCode, int checkListPage) {
  static unsigned long cMillis;
  cMillis = millis();
  
  CheckListPage = checkListPage;

  static PushButton topScreen;
  topScreen.runCallBack(pbCode == PB_TOP_SCREEN ? 0 : 1, []() {
    radios.displayCheckListsTopScreenBtn();
  });

  static PushButton middleScreen;
  middleScreen.runCallBack(pbCode == PB_MIDDLE_SCREEN ? 0 : 1, []() {
    radios.displayCheckListsMiddleScreenBtn();
  });

  static PushButton bottomScreen;
  bottomScreen.runCallBack(pbCode == PB_BOTTOM_SCREEN ? 0 : 1, []() {
    radios.displayCheckListsBottomScreenBtn();
  });

  static PushButton menu;
  menu.runCallBack(pbCode == PB_MENU ? 0 : 1, []() {
    radios.displayCheckListsMenuBtn();
  });

  // switch between A-10C / A-10C II
  static PushButton a10VersionSwitch;
  a10VersionSwitch.runCallBack(pbCode == PB_XMTRCV ? 0 : 1, []() {
    radios.switchA10Version();
  });

  static PushButton pbFrequenctSelector1;
  pbFrequenctSelector1.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_1 ? 0 : 1, []() {
    radios.displayCheckListsPage(1);
  });

  static PushButton pbFrequenctSelector2;
  pbFrequenctSelector2.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_2 ? 0 : 1, []() {
    radios.displayCheckListsPage(2);
  });

  static PushButton pbFrequenctSelector3;
  pbFrequenctSelector3.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_3 ? 0 : 1, []() {
    radios.displayCheckListsPage(3);
  });

  static PushButton pbFrequenctSelector4;
  pbFrequenctSelector4.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_4 ? 0 : 1, []() {
    radios.displayCheckListsPage(4);
  });

  static PushButton pbFrequenctSelector5;
  pbFrequenctSelector5.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_5 ? 0 : 1, []() {
    radios.displayCheckListsPage(5);
  });

  static PushButton channel;
  static PushButton nvhChannelJoy(I2C_DATA, BUTTON_INDEX[BTN_NVG_TOGGLE]); 
  channel.runCallBack(pbCode == PB_CHANNEL ? 0 : 1, []() {
    switch (CheckListPage) {
      case 61: radios.sendDcsCommand("FQIS_TEST", "1"); break; // Fuel
      case 62: nvhChannelJoy.run(0); // Nvg
      default: break;
    }
  }, []() {
    switch (CheckListPage) {
      case 61: radios.sendDcsCommand("FQIS_TEST", "0"); break; // Fuel
      case 62: nvhChannelJoy.run(1); // Nvg
      default: break;
    }
  });

  static KnobJoy knobNvgChannel(I2C_DATA, 33, 32);
  switch (CheckListPage) {
    case 62: knobNvgChannel.runIndefiniteLeftRight(BUTTON_INDEX[BTN_NVG_DEC], BUTTON_INDEX[BTN_NVG_INC], &cMillis);
    default: break;
  }  
}
#endif

