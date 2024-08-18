#ifndef checklistsCommands_h
#define checklistsCommands_h

#include "PushButton.h"

void checklistsCommands(int pbCode) {
  static PushButton topScreen;
  topScreen.runCallBack(pbCode == PB_TOP_SCREEN ? 0 : 1, []() {
    radios.displayCheckListsTopScreenBtn();
  });

  static PushButton middleScreen;
  middleScreen.runCallBack(pbCode == PB_MIDDLE_SCREEN ? 0 : 1, []() {
    radios.displayCheckListsMiddleScreenBtn();
  });

  static PushButton bottomScreen;
  topScreen.runCallBack(pbCode == PB_BOTTOM_SCREEN ? 0 : 1, []() {
    radios.displayCheckListsBottomScreenBtn();
  });

  static PushButton menu;
  menu.runCallBack(pbCode == PB_MENU ? 0 : 1, []() {
    radios.displayCheckListsMenuBtn();
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
}
#endif

