#ifndef Cmsp_h
#define Cmsp_h

#include "Arduino.h"
#include "PushButton.h"
#include "LiquidCrystal_I2C_DFRobot.h"

#define LCD_ADRESS 0x27
#define LCD_COLUMN 20
#define LCD_ROW 4

LiquidCrystal_I2C lcd(LCD_ADRESS, LCD_COLUMN, LCD_ROW);

void setupCmsp() {
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);

  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  pinMode(18, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);

  lcd.init();
	lcd.backlight();
  lcd.setCursor(0, 0);
}

void cmspPrintLcd(char* newValue, int line, int row) {
  lcd.setCursor(row, line);
  lcd.print(newValue);
}

int currentCmspMode = -1;
bool lastePressedStateCmsp = false;

void runCmsp() {
  static int numSampleCmsp = 0;
  static int samplesCmsp[ANALOG_SAMPLE];
  static int analogMeanCmsp = 0;
  PushButton::getPBCode(analogRead(A8), &numSampleCmsp, samplesCmsp, &analogMeanCmsp, 1000, 1025);
  // OFF
  if (currentCmspMode != 0 && analogMeanCmsp >= 612 && analogMeanCmsp <= 614) {
    sendDcsCommand("CMSP_MODE", "0");
    currentCmspMode = 0;
  }
  // stby
  else if (currentCmspMode != 1 && analogMeanCmsp >= 0 && analogMeanCmsp <= 4) {
    sendDcsCommand("CMSP_MODE", "1");
    currentCmspMode = 1;
  }
  // man
  else if (currentCmspMode != 2 && analogMeanCmsp >= 516 && analogMeanCmsp <= 520) {
    sendDcsCommand("CMSP_MODE", "2");
    currentCmspMode = 2;
  }
  // semi
  else if (currentCmspMode != 3 && analogMeanCmsp >= 752 && analogMeanCmsp <= 754) {
    sendDcsCommand("CMSP_MODE", "3");
    currentCmspMode = 3;
  }
  // auto
  else if (currentCmspMode != 4 && analogMeanCmsp >= 673 && analogMeanCmsp <= 677) {
    sendDcsCommand("CMSP_MODE", "4");
    currentCmspMode = 4;
  }


  static int numSampleCmspBtn = 0;
  static int samplesCmspBtn[ANALOG_SAMPLE];
  static int analogMeanCmspBtn = 0;
  int a9Read = analogRead(A9);
  PushButton::getPBCode(a9Read, &numSampleCmspBtn, samplesCmspBtn, &analogMeanCmspBtn, 690, 695);

  if (lastePressedStateCmsp == false && analogMeanCmspBtn == 0 && a9Read > 5) {
    // raf
  } else {
    lastePressedStateCmsp = true;

    // Cmsc JMR 2
    static PushButton cmscJmr;
    cmscJmr.runCallBack((analogMeanCmspBtn >= 0 && analogMeanCmspBtn <= 5 && a9Read <= 5) ? 0 : 1, []() {
      sendDcsCommand("CMSC_JMR", "1");
    }, []() {
      sendDcsCommand("CMSC_JMR", "0");
      lastePressedStateCmsp = false;
    });

    // Cmsc PRI 252
    static PushButton cmscPri;
    cmscPri.runCallBack((analogMeanCmspBtn >= 250 && analogMeanCmspBtn <= 255) ? 0 : 1, []() {
      sendDcsCommand("CMSC_PRI", "1");
    }, []() {
      sendDcsCommand("CMSC_PRI", "0");
      lastePressedStateCmsp = false;
    });

    // Cmsc SEP 388
    static PushButton cmscSep;
    cmscSep.runCallBack((analogMeanCmspBtn >= 386 && analogMeanCmspBtn <= 401) ? 0 : 1, []() {
      sendDcsCommand("CMSC_SEP", "1");
    }, []() {
      sendDcsCommand("CMSC_SEP", "0");
      lastePressedStateCmsp = false;
    });
    
    // Cmsp EDIT1 477
    static PushButton cmspEdit1;
    cmspEdit1.runCallBack((analogMeanCmspBtn >= 475 && analogMeanCmspBtn <= 480) ? 0 : 1, []() {
      sendDcsCommand("CMSP_ARW1", "1");
    }, []() {
      sendDcsCommand("CMSP_ARW1", "0");
      lastePressedStateCmsp = false;
    });

    // Cmsp EDIT2 543
    static PushButton cmspEdit2;
    cmspEdit2.runCallBack((analogMeanCmspBtn >= 541 && analogMeanCmspBtn <= 546) ? 0 : 1, []() {
      sendDcsCommand("CMSP_ARW2", "1");
    }, []() {
      sendDcsCommand("CMSP_ARW2", "0");
      lastePressedStateCmsp = false;
    });

    // Cmsp EDIT3 598
    static PushButton cmspEdit3;
    cmspEdit3.runCallBack((analogMeanCmspBtn >= 596 && analogMeanCmspBtn <= 601) ? 0 : 1, []() {
      sendDcsCommand("CMSP_ARW3", "1");
    }, []() {
      sendDcsCommand("CMSP_ARW3", "0");
      lastePressedStateCmsp = false;
    });

    // Cmsp EDIT4 650
    static PushButton cmspEdit4;
    cmspEdit4.runCallBack((analogMeanCmspBtn >= 648 && analogMeanCmspBtn <= 653) ? 0 : 1, []() {
      sendDcsCommand("CMSP_ARW4", "1");
    }, []() {
      sendDcsCommand("CMSP_ARW4", "0");
      lastePressedStateCmsp = false;
    });

    // Cmsp NXT UP 703
    static PushButton cmspNxtUp;
    cmspNxtUp.runCallBack((analogMeanCmspBtn >= 701 && analogMeanCmspBtn <= 706) ? 0 : 1, []() {
      sendDcsCommand("CMSP_UPDN", "2");
    }, []() {
      sendDcsCommand("CMSP_UPDN", "1");
      lastePressedStateCmsp = false;
    });
    // Cmsp NXT DOWN 768
    static PushButton cmspNxtDn;
    cmspNxtDn.runCallBack((analogMeanCmspBtn >= 766 && analogMeanCmspBtn <= 771) ? 0 : 1, []() {
      sendDcsCommand("CMSP_UPDN", "0");
    }, []() {
      sendDcsCommand("CMSP_UPDN", "1");
      lastePressedStateCmsp = false;
    });
    // Cmsp RTN 859
    static PushButton cmspRtn;
    cmspRtn.runCallBack((analogMeanCmspBtn >= 857 && analogMeanCmspBtn <= 862) ? 0 : 1, []() {
      sendDcsCommand("CMSP_RTN", "1");
    }, []() {
      sendDcsCommand("CMSP_RTN", "0");
      lastePressedStateCmsp = false;
    });
  }

  ///////////////////////////////////
  static PushButton pin2;
  pin2.runCallBack(bitRead(PINE, PINE4), []() {
    sendDcsCommand("CMSP_DISP", "2"); // Disp menu
  }, []() {
    sendDcsCommand("CMSP_DISP", "1"); // Disp ON
  });
  static PushButton pin3;
  pin3.runCallBack(bitRead(PINE, PINE5), []() {
    sendDcsCommand("CMSP_DISP", "0"); // DISP OFF
  }, []() {
    sendDcsCommand("CMSP_DISP", "1"); // DISP ON
  });

  static PushButton pin4;
  pin4.runCallBack(bitRead(PING, PING5), []() {
    sendDcsCommand("CMSP_RWR", "2"); // RWR menu
  }, []() {
    sendDcsCommand("CMSP_RWR", "1"); // RWR ON
  });
  static PushButton pin15;
  pin15.runCallBack(bitRead(PINJ, PINJ0), []() {
    sendDcsCommand("CMSP_RWR", "0"); // RWR OFF
  }, []() {
    sendDcsCommand("CMSP_RWR", "1"); // RWR ON
  });


  static PushButton pin5;
  pin5.runCallBack(bitRead(PINE, PINE3), []() {
    sendDcsCommand("CMSP_JMR", "2"); // JMR menu
  }, []() {
    sendDcsCommand("CMSP_JMR", "1"); // JMR ON
  });
  static PushButton pin16;
  pin16.runCallBack(bitRead(PINH, PINH1), []() {
    sendDcsCommand("CMSP_JMR", "0"); // RWR OFF
  }, []() {
    sendDcsCommand("CMSP_JMR", "1"); // RWR ON
  });


  static PushButton pin14;
  pin14.runCallBack(bitRead(PINJ, PINJ1), []() {
    sendDcsCommand("CMSP_JTSN", "1");
  }, []() {
    sendDcsCommand("CMSP_JTSN", "0");
  });


  static PushButton pin17;
  pin17.runCallBack(bitRead(PINH, PINH0), []() {
    sendDcsCommand("CMSP_MWS", "2"); // NWS menu
  }, []() {
    sendDcsCommand("CMSP_MWS", "1"); // NWS ON
  });
  static PushButton pin18;
  pin18.runCallBack(bitRead(PIND, PIND3), []() {
    sendDcsCommand("CMSP_MWS", "0"); // NWS OFF
  }, []() {
    sendDcsCommand("CMSP_MWS", "1"); // NWS ON
  });
}

#endif
