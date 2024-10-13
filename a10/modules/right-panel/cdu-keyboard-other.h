#ifndef CduKeyboardOther_h
#define CduKeyboardOther_h

#include "Arduino.h"
#include "PushButton.h"


void setupCduKeyboardOther() {
  pinMode(A14, INPUT);
}

bool lastePressedStateCduOther = false;

void runCduKeyboardOther() {
  
  static int numSampleCduOther = 0;
  static int samplesCduOther[ANALOG_SAMPLE];
  static int analogMeanCduOther = 0;
  PushButton::getPBCode(analogRead(A14), &numSampleCduOther, samplesCduOther, &analogMeanCduOther, 407, 411);

  if (lastePressedStateCduOther == false && analogMeanCduOther == 0) {
    return;
  }

  lastePressedStateCduOther = true;

  static PushButton cduPup;
  cduPup.runCallBack((analogMeanCduOther >= 448 && analogMeanCduOther <= 452) ? 0 : 1, []() {
    sendDcsCommand("CDU_PG", "2");
  }, []() {
    sendDcsCommand("CDU_PG", "1");
    lastePressedStateCduOther = false;
  });

  static PushButton cduPdown;
  cduPdown.runCallBack((analogMeanCduOther >= 419 && analogMeanCduOther <= 423) ? 0 : 1, []() {
    sendDcsCommand("CDU_PG", "0");
  }, []() {
    sendDcsCommand("CDU_PG", "1");
    lastePressedStateCduOther = false;
  });

  static PushButton cduOtherPoint;
  cduOtherPoint.runCallBack((analogMeanCduOther >= 478 && analogMeanCduOther <= 482) ? 0 : 1, []() {
    // No function
  }, []() {
    // No function
    lastePressedStateCduOther = false;
  });

  static PushButton cduMk;
  cduMk.runCallBack((analogMeanCduOther >= 391 && analogMeanCduOther <= 393) ? 0 : 1, []() {
    sendDcsCommand("CDU_MK", "1");
  }, []() {
    sendDcsCommand("CDU_MK", "0");
    lastePressedStateCduOther = false;
  });

  static PushButton cduOtherBlank;
  cduOtherBlank.runCallBack((analogMeanCduOther >= 512 && analogMeanCduOther <= 516) ? 0 : 1, []() {
    // No function
  }, []() {
    // No function
    lastePressedStateCduOther = false;
  });

  static PushButton cduBck;
  cduBck.runCallBack((analogMeanCduOther >= 552 && analogMeanCduOther <= 556) ? 0 : 1, []() {
    sendDcsCommand("CDU_BCK", "1");
  }, []() {
    sendDcsCommand("CDU_BCK", "0");
    lastePressedStateCduOther = false;
  });

  static PushButton cduSpc;
  cduSpc.runCallBack((analogMeanCduOther >= 604 && analogMeanCduOther <= 608) ? 0 : 1, []() {
    sendDcsCommand("CDU_SPC", "1");
  }, []() {
    sendDcsCommand("CDU_SPC", "0");
    lastePressedStateCduOther = false;
  });  

  static PushButton cduScrollDown;
  cduScrollDown.runCallBack((analogMeanCduOther >= 388 && analogMeanCduOther <= 390) ? 0 : 1, []() {
    sendDcsCommand("CDU_SCROLL", "0");
  }, []() {
    sendDcsCommand("CDU_SCROLL", "1");
    lastePressedStateCduOther = false;
  });

  static PushButton cduScrollUp;
  cduScrollUp.runCallBack((analogMeanCduOther >= 353 && analogMeanCduOther <= 357) ? 0 : 1, []() {
    sendDcsCommand("CDU_SCROLL", "2");
  }, []() {
    sendDcsCommand("CDU_SCROLL", "1");
    lastePressedStateCduOther = false;
  });  

  static PushButton cduY;
  cduY.runCallBack((analogMeanCduOther >= 678 && analogMeanCduOther <= 682) ? 0 : 1, []() {
    sendDcsCommand("CDU_Y", "1");
  }, []() {
    sendDcsCommand("CDU_Y", "0");
    lastePressedStateCduOther = false;
  });

  static PushButton cduZ;
  cduZ.runCallBack((analogMeanCduOther >= 795 && analogMeanCduOther <= 799) ? 0 : 1, []() {
    sendDcsCommand("CDU_Z", "1");
  }, []() {
    sendDcsCommand("CDU_Z", "0");
    lastePressedStateCduOther = false;
  });

  static PushButton cduClr;
  cduClr.runCallBack((analogMeanCduOther >= 311 && analogMeanCduOther <= 315) ? 0 : 1, []() {
    sendDcsCommand("CDU_CLR", "1");
  }, []() {
    sendDcsCommand("CDU_CLR", "0");
    lastePressedStateCduOther = false;
  });

  static PushButton cduFa;
  cduFa.runCallBack((analogMeanCduOther >= 254 && analogMeanCduOther <= 258) ? 0 : 1, []() {
    sendDcsCommand("CDU_FA", "1");
  }, []() {
    sendDcsCommand("CDU_FA", "0");
    lastePressedStateCduOther = false;
  });

  static PushButton cduDataUp;
  cduDataUp.runCallBack((analogMeanCduOther >= 1020 && analogMeanCduOther <= 1025) ? 0 : 1, []() {
    sendDcsCommand("CDU_DATA", "2");
  }, []() {
    sendDcsCommand("CDU_DATA", "1");
    lastePressedStateCduOther = false;
  });

  static PushButton cduDataDown;
  cduDataDown.runCallBack((analogMeanCduOther >= 165 && analogMeanCduOther <= 169) ? 0 : 1, []() {
    sendDcsCommand("CDU_DATA", "0");
  }, []() {
    sendDcsCommand("CDU_DATA", "1");
    lastePressedStateCduOther = false;
  });
}

#endif
