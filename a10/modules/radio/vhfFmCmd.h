#ifndef vhfFmCmd_h
#define vhfFmCmd_h

#include "PushButton.h"
#include "KnobJoy.h"

void vhfFmCommands(int pbCode) {
  static KnobJoy channel(I2C_DATA, 33, 32);
  channel.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_PRESET", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_PRESET", "INC");
  });

  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_FREQ1", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_FREQ1", "INC");
  });

  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_FREQ2", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_FREQ2", "INC");
  });

  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_FREQ3", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_FREQ3", "INC");
  });

  static KnobJoy freqSelector4(I2C_DATA, 35, 34);
  freqSelector4.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_FREQ4", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_FREQ4", "INC");
  });

  static KnobJoy masterMode(I2C_DATA, 25, 24);
  masterMode.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_FREQEMER", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_FREQEMER", "INC");
  });

  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  secondaryMode.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_MODE", "DEC");
  }, []() {
    radios.sendDcsCommand("VHFFM_MODE", "INC");
  });

  static KnobJoy volume(I2C_DATA, 39, 38);
  volume.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_VOL", "-1500");
  }, []() {
    radios.sendDcsCommand("VHFFM_VOL", "+1500");
  });

  static KnobJoy squelch(I2C_DATA, 41, 40);
  squelch.runCallBack([]() {
    radios.sendDcsCommand("VHFFM_SQUELCH", "0");
  }, []() {
    radios.sendDcsCommand("VHFFM_SQUELCH", "1");
  }); 

  static PushButton load;
  load.runCallBack(pbCode == PB_CHANNEL ? 0 : 1, []() {
    radios.sendDcsCommand("VHFFM_LOAD", "1");
  }, []() {
    radios.sendDcsCommand("VHFFM_LOAD", "0");
  });
}
#endif

