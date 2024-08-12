#ifndef arc210Cmd_h
#define arc210Cmd_h

#include "PushButton.h"
#include "KnobJoy.h"

void arc210Commands(int pbCode) {
  // Serial.println(pbCode);

  static PushButton fskUpper;
  fskUpper.runCallBack(pbCode == PB_TOP_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_FSK_UP", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_FSK_UP", "0");
  });
  
  static PushButton fskMiddle;
  fskMiddle.runCallBack(pbCode == PB_MIDDLE_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_FSK_MID", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_FSK_MID", "0");
  });

  static PushButton fskLower;
  fskLower.runCallBack(pbCode == PB_BOTTOM_SCREEN ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_FSK_LOW", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_FSK_LOW", "0");
  });

  /*
  static PushButton micSwitchFwd();
  micSwitchFwd.runCallBack(pbCode == PB_VOLUME ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_FSK_LOW", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_FSK_LOW", "0");
  });
  */

  static PushButton amFm;
  amFm.runCallBack(pbCode == PB_AMFM ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_AMP_FREQ_MODUL", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_AMP_FREQ_MODUL", "0");
  });

  static PushButton menu;
  menu.runCallBack(pbCode == PB_MENU ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_MENU", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_MENU", "0");
  });

  static PushButton offset;
  offset.runCallBack(pbCode == PB_OFFSET ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_OFF_FREQ", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_OFF_FREQ", "0");
  });

  static PushButton xmtRcv;
  xmtRcv.runCallBack(pbCode == PB_XMTRCV ? 0 : 1, []() {
    radios.sendDcsCommand("ARC210_TRANS_REC_FUNC", "1");
  }, []() {
    radios.sendDcsCommand("ARC210_TRANS_REC_FUNC", "0");
  });
  
  // Maron
  static KnobJoy freqSelector1(I2C_DATA, 23, 22);
  freqSelector1.runCallBack([]() {
    radios.sendDcsCommand("ARC210_100MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_100MHZ_SEL", "INC");
  });

  // Rouge
  static KnobJoy masterMode(I2C_DATA, 25, 24);
  masterMode.runCallBack([]() {
    radios.sendDcsCommand("ARC210_MASTER", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_MASTER", "INC");
  });

  // Jaune
  static KnobJoy freqSelector2(I2C_DATA, 28, 29);
  freqSelector2.runCallBack([]() {
    radios.sendDcsCommand("ARC210_10MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_10MHZ_SEL", "INC");
  });

  // Vert
  static KnobJoy freqSelector3(I2C_DATA, 31, 30);
  freqSelector3.runCallBack([]() {
    radios.sendDcsCommand("ARC210_1MHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_1MHZ_SEL", "INC");
  });

  // Bleu
  static KnobJoy channel(I2C_DATA, 33, 32);
  channel.runCallBack([]() {
    radios.sendDcsCommand("ARC210_CHN_KNB", "-10");
  }, []() {
    radios.sendDcsCommand("ARC210_CHN_KNB", "+10");
  });

  // Violet
  static KnobJoy freqSelector4(I2C_DATA, 35, 34);
  freqSelector4.runCallBack([]() {
    radios.sendDcsCommand("ARC210_100KHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_100KHZ_SEL", "INC");
  });

  // Gris
  static KnobJoy secondaryMode(I2C_DATA, 37, 36);
  secondaryMode.runCallBack([]() {
    radios.sendDcsCommand("ARC210_SEC_SW", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_SEC_SW", "INC");
  });

  // Blanc -> volume knob n/a

  // Noir
  static KnobJoy squelch(I2C_DATA, 41, 40);
  squelch.runCallBack([]() {
    radios.sendDcsCommand("ARC210_SQUELCH", "0");
  }, []() {
    radios.sendDcsCommand("ARC210_SQUELCH", "1");
  });  

  // Marron
  static KnobJoy freqSelector5(I2C_DATA, 42, 43);
  freqSelector5.runCallBack([]() {
    radios.sendDcsCommand("ARC210_25KHZ_SEL", "DEC");
  }, []() {
    radios.sendDcsCommand("ARC210_25KHZ_SEL", "INC");
  });
}
#endif

