#ifndef uhfCmd_h
#define uhfCmd_h

#include "PushButton.h"
#include "KnobJoy.h"
#include "AutoReleaseSwitch.h"

void uhfCommands(int pbCode) {
  static KnobJoy channel(I2C_DATA, 33, 32);
  channel.runCallBack([]() {
    radios.sendDcsCommand("UHF_PRESET_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_PRESET_SEL", "INC");
  });

  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runCallBack([]() {
    radios.sendDcsCommand("UHF_100MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_100MHZ_SEL", "INC");
  });

  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("UHF_10MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_10MHZ_SEL", "INC");
  });

  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("UHF_1MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_1MHZ_SEL", "INC");
  });

  static KnobJoy freqSelector4(I2C_DATA, 35, 34);
  freqSelector4.runCallBack([]() {
    radios.sendDcsCommand("UHF_POINT1MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_POINT1MHZ_SEL", "INC");
  });

  static KnobJoy freqSelector5(I2C_DATA, 42, 43);
  freqSelector5.runCallBack([]() {
    radios.sendDcsCommand("UHF_POINT25_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_POINT25_SEL", "INC");
  });

  static KnobJoy masterMode(I2C_DATA, 25, 24);
  masterMode.runCallBack([]() {
    radios.sendDcsCommand("UHF_FUNCTION", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_FUNCTION", "INC");
  });

  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  secondaryMode.runCallBack([]() {
    radios.sendDcsCommand("UHF_MODE", "DEC");
  }, []() {
    radios.sendDcsCommand("UHF_MODE", "INC");
  });

  static KnobJoy volume(I2C_DATA, 39, 38);
  volume.runCallBack([]() {
    radios.sendDcsCommand("UHF_VOL", "-1500");
  }, []() {
    radios.sendDcsCommand("UHF_VOL", "+1500");
  });

  static KnobJoy squelch(I2C_DATA, 41, 40);
  squelch.runCallBack([]() {
    radios.sendDcsCommand("UHF_SQUELCH", "0");
  }, []() {
    radios.sendDcsCommand("UHF_SQUELCH", "1");
  }); 

  static PushButton fskUpper;
  fskUpper.runCallBack(pbCode == PB_TOP_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("UHF_T_TONE", "0");
  }, []() {});
  
  static PushButton fskMiddle;
  fskMiddle.runCallBack(pbCode == PB_MIDDLE_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("UHF_T_TONE", "1");
  }, []() {});

  static PushButton fskLower;
  fskLower.runCallBack(pbCode == PB_BOTTOM_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("UHF_T_TONE", "2");
  }, []() {});
}
#endif

