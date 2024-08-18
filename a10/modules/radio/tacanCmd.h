#ifndef tacanCmd_h
#define tacanCmd_h

#include "PushButton.h"
#include "KnobJoy.h"

void tacanCommands(int pbCode) {
  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runCallBack([]() {
    radios.sendDcsCommand("TACAN_10", "DEC");
  }, []() {
    radios.sendDcsCommand("TACAN_10", "INC");
  });

  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("TACAN_1", "DEC");
  }, []() {
    radios.sendDcsCommand("TACAN_1", "INC");
  });

  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("TACAN_XY", "DEC");
  }, []() {
    radios.sendDcsCommand("TACAN_XY", "INC");
  });

  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  secondaryMode.runCallBack([]() {
    radios.sendDcsCommand("TACAN_MODE", "DEC");
  }, []() {
    radios.sendDcsCommand("TACAN_MODE", "INC");
  });

  static KnobJoy volume(I2C_DATA, 39, 38);
  volume.runCallBack([]() {
    radios.sendDcsCommand("TACAN_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("TACAN_VOL", "+3200");
  });

  static PushButton load;
  load.runCallBack(pbCode == PB_CHANNEL ? 0 : 1, []() {
    radios.sendDcsCommand("TACAN_TEST_BTN", "1");
  }, []() {
    radios.sendDcsCommand("TACAN_TEST_BTN", "0");
  });
}
#endif

