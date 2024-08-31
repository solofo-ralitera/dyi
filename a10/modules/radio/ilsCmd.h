#ifndef ilsCmd_h
#define ilsCmd_h

#include "PushButton.h"
#include "KnobJoy.h"

void ilsCommands(int pbCode) {
  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("ILS_MHZ", "DEC");
  }, []() {
    radios.sendDcsCommand("ILS_MHZ", "INC");
  });

  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("ILS_KHZ", "DEC");
  }, []() {
    radios.sendDcsCommand("ILS_KHZ", "INC");
  });

  static KnobJoy masterMode(I2C_DATA, 25, 24);
  masterMode.runCallBack([]() {
    radios.sendDcsCommand("ILS_PWR", "DEC");
  }, []() {
    radios.sendDcsCommand("ILS_PWR", "INC");
  });

  static KnobJoy squelch(I2C_DATA, 41, 40);
  squelch.runCallBack([]() {
    radios.sendDcsCommand("INT_ILS_UNMUTE", "0");
  }, []() {
    radios.sendDcsCommand("INT_ILS_UNMUTE", "1");
  }); 

  static KnobJoy volume(I2C_DATA, 39, 38);
  volume.runCallBack([]() {
    radios.sendDcsCommand("ILS_VOL", "-3200");
  }, []() {
    radios.sendDcsCommand("ILS_VOL", "+3200");
  });
}
#endif

