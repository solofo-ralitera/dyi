#ifndef vhfAmCmd_h
#define vhfAmCmd_h

#include "PushButton.h"
#include "KnobJoy.h"

void vhfAmCommands(int pbCode) {
  static KnobJoy channel(I2C_DATA, 33, 32);
  channel.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_PRESET", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_PRESET", "INC");
  });

  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_FREQ1", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_FREQ1", "INC");
  });

  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_FREQ2", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_FREQ2", "INC");
  });

  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_FREQ3", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_FREQ3", "INC");
  });

  static KnobJoy freqSelector4(I2C_DATA, 35, 34);
  freqSelector4.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_FREQ4", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_FREQ4", "INC");
  });

  static KnobJoy masterMode(I2C_DATA, 25, 24);
  masterMode.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_FREQEMER", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_FREQEMER", "INC");
  });

  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  secondaryMode.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_MODE", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFAM_MODE", "INC");
  });

  static KnobJoy volume(I2C_DATA, 39, 38);
  volume.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_VOL", "-1500");
  }, []() {
    radios.sendDcsCommand("VHFAM_VOL", "+1500");
  });

  static KnobJoy squelch(I2C_DATA, 41, 40);
  squelch.runCallBack([]() {
    radios.sendDcsCommand("VHFAM_SQUELCH", "0");
  }, []() {
    radios.sendDcsCommand("VHFAM_SQUELCH", "1");
  }); 

  static PushButton load;
  load.runCallBack(pbCode == PB_CHANNEL ? 0 : 1, []() {
    radios.sendDcsCommand("VHFAM_LOAD", "1");
  }, []() {
    radios.sendDcsCommand("VHFAM_LOAD", "0");
  });

  static PushButton micSwitchFwd;
  static PushButton micSwitchFwdJoy(I2C_DATA, BUTTON_INDEX[BTN_MIC_SWITCH_FWD]);  
  micSwitchFwd.runCallBack(pbCode == PB_MOD_SELECTOR ? 0 : 1, []() {
    micSwitchFwdJoy.run(0);
  }, []() {
    micSwitchFwdJoy.run(1);
  });
}
#endif

