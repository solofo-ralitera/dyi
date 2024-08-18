#ifndef intercomPanel_h
#define intercomPanel_h

#include "PushButton.h"
#include "KnobJoy.h"

void intercomPanelCommands(int pbCode) {
  static KnobJoy volume(I2C_DATA, 39, 38);
  volume.runCallBack([]() {
    radios.sendDcsCommand("INT_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("INT_VOL", "+3200");
  });

  static PushButton channelBtn;
  channelBtn.runCallBack(pbCode == PB_CHANNEL ? 0 : 1, []() {
    radios.sendDcsCommand("INT_HM", "TOGGLE");
  });

  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  secondaryMode.runCallBack([]() {
    radios.sendDcsCommand("INT_MODE", "DEC");
  }, []() {
    radios.sendDcsCommand("INT_MODE", "INC");
  });

  // INT
  static PushButton pbFrequenctSelector1;
  pbFrequenctSelector1.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_1 ? 0 : 1, []() {
    radios.sendDcsCommand("INT_INT_UNMUTE", "TOGGLE");
  });

  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runCallBack([]() {
    radios.sendDcsCommand("INT_INT_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("INT_INT_VOL", "+3200");
  });

  // AIM
  static PushButton pbFrequenctSelector2;
  pbFrequenctSelector2.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_2 ? 0 : 1, []() {
    radios.sendDcsCommand("INT_AIM_UNMUTE", "TOGGLE");
  });

  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("INT_AIM_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("INT_AIM_VOL", "+3200");
  });

  // FM
  static PushButton pbFrequenctSelector3;
  pbFrequenctSelector3.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_3 ? 0 : 1, []() {
    radios.sendDcsCommand("INT_FM_UNMUTE", "TOGGLE");
  });

  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("INT_FM_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("INT_FM_VOL", "+3200");
  });  

  // UHF
  static PushButton pbFrequenctSelector4;
  pbFrequenctSelector4.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_4 ? 0 : 1, []() {
    radios.sendDcsCommand("INT_VHF_UNMUTE", "TOGGLE");
  });

  static KnobJoy freqSelector4(I2C_DATA, 35, 34);
  freqSelector4.runCallBack([]() {
    radios.sendDcsCommand("INT_VHF_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("INT_VHF_VOL", "+3200");
  });

  // VHF
  static PushButton pbFrequenctSelector5;
  pbFrequenctSelector5.runCallBack(pbCode == PB_FREQUENCY_SELECTOR_5 ? 0 : 1, []() {
    radios.sendDcsCommand("INT_UHF_UNMUTE", "TOGGLE");
  });

  static KnobJoy freqSelector5(I2C_DATA, 42, 43);
  freqSelector5.runCallBack([]() {
    radios.sendDcsCommand("INT_UHF_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("INT_UHF_VOL", "+3200");
  });
}
#endif

