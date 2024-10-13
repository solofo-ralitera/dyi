#ifndef CduKeyboardAlpha_h
#define CduKeyboardAlpha_h

#include "Arduino.h"
#include "PushButton.h"


void setupCduKeyboardAlpha() {
  pinMode(A13, INPUT);
}

bool lastePressedStateCduAlpha = false;

void runCduKeyboardAlpha() {
  static int numSampleCduAlpha = 0;
  static int samplesCduAlpha[ANALOG_SAMPLE];
  static int analogMeanCduAlpha = 0;
  PushButton::getPBCode(analogRead(A13), &numSampleCduAlpha, samplesCduAlpha, &analogMeanCduAlpha, 407, 411);

  if (lastePressedStateCduAlpha == false && analogMeanCduAlpha == 0) {
    return;
  }

  lastePressedStateCduAlpha = true;

  static PushButton cduA;
  cduA.runCallBack((analogMeanCduAlpha >= 556 && analogMeanCduAlpha <= 560 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_A", "1");
  }, []() {
    sendDcsCommand("CDU_A", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduB;
  cduB.runCallBack((analogMeanCduAlpha >= 590 && analogMeanCduAlpha <= 594 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_B", "1");
  }, []() {
    sendDcsCommand("CDU_B", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduC;
  cduC.runCallBack((analogMeanCduAlpha >= 636 && analogMeanCduAlpha <= 640 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_C", "1");
  }, []() {
    sendDcsCommand("CDU_C", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduD;
  cduD.runCallBack((analogMeanCduAlpha >= 703 && analogMeanCduAlpha <= 707 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_D", "1");
  }, []() {
    sendDcsCommand("CDU_D", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduE;
  cduE.runCallBack((analogMeanCduAlpha >= 812 && analogMeanCduAlpha <= 816 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_E", "1");
  }, []() {
    sendDcsCommand("CDU_E", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduF;
  cduF.runCallBack((analogMeanCduAlpha >= 1020 && analogMeanCduAlpha <= 1025 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_F", "1");
  }, []() {
    sendDcsCommand("CDU_F", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduG;
  cduG.runCallBack((analogMeanCduAlpha >= 530 && analogMeanCduAlpha <= 534 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_G", "1");
  }, []() {
    sendDcsCommand("CDU_G", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduH;
  cduH.runCallBack((analogMeanCduAlpha >= 508 && analogMeanCduAlpha <= 512 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_H", "1");
  }, []() {
    sendDcsCommand("CDU_H", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduI;
  cduI.runCallBack((analogMeanCduAlpha >= 490 && analogMeanCduAlpha <= 494 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_I", "1");
  }, []() {
    sendDcsCommand("CDU_I", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduJ;
  cduJ.runCallBack((analogMeanCduAlpha >= 474 && analogMeanCduAlpha <= 478 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_J", "1");
  }, []() {
    sendDcsCommand("CDU_J", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduK;
  cduK.runCallBack((analogMeanCduAlpha >= 460 && analogMeanCduAlpha <= 464 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_K", "1");
  }, []() {
    sendDcsCommand("CDU_K", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduL;
  cduL.runCallBack((analogMeanCduAlpha >= 447 && analogMeanCduAlpha <= 451 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_L", "1");
  }, []() {
    sendDcsCommand("CDU_L", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduM;
  cduM.runCallBack((analogMeanCduAlpha >= 354 && analogMeanCduAlpha <= 358 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_M", "1");
  }, []() {
    sendDcsCommand("CDU_M", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduN;
  cduN.runCallBack((analogMeanCduAlpha >= 371 && analogMeanCduAlpha <= 375 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_N", "1");
  }, []() {
    sendDcsCommand("CDU_N", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduO;
  cduO.runCallBack((analogMeanCduAlpha >= 386 && analogMeanCduAlpha <= 390 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_O", "1");
  }, []() {
    sendDcsCommand("CDU_O", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduP;
  cduP.runCallBack((analogMeanCduAlpha >= 400 && analogMeanCduAlpha <= 404 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_P", "1");
  }, []() {
    sendDcsCommand("CDU_P", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduQ;
  cduQ.runCallBack((analogMeanCduAlpha >= 422 && analogMeanCduAlpha <= 426 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_Q", "1");
  }, []() {
    sendDcsCommand("CDU_Q", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduR;
  cduR.runCallBack((analogMeanCduAlpha >= 435 && analogMeanCduAlpha <= 438 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_R", "1");
  }, []() {
    sendDcsCommand("CDU_R", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduS;
  cduS.runCallBack((analogMeanCduAlpha >= 332 && analogMeanCduAlpha <= 336 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_S", "1");
  }, []() {
    sendDcsCommand("CDU_S", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduT;
  cduT.runCallBack((analogMeanCduAlpha >= 306 && analogMeanCduAlpha <= 310 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_T", "1");
  }, []() {
    sendDcsCommand("CDU_T", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduU;
  cduU.runCallBack((analogMeanCduAlpha >= 271 && analogMeanCduAlpha <= 275) ? 0 : 1, []() {
    sendDcsCommand("CDU_U", "1");
  }, []() {
    sendDcsCommand("CDU_U", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduV;
  cduV.runCallBack((analogMeanCduAlpha >= 219 && analogMeanCduAlpha <= 223) ? 0 : 1, []() {
    sendDcsCommand("CDU_V", "1");
  }, []() {
    sendDcsCommand("CDU_V", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduW;
  cduW.runCallBack((analogMeanCduAlpha >= 136 && analogMeanCduAlpha <= 140) ? 0 : 1, []() {
    sendDcsCommand("CDU_W", "1");
  }, []() {
    sendDcsCommand("CDU_W", "0");
    lastePressedStateCduAlpha = false;
  });

  static PushButton cduX;
  cduX.runCallBack((analogMeanCduAlpha >= 57 && analogMeanCduAlpha <= 61) ? 0 : 1, []() {
    sendDcsCommand("CDU_X", "1");
  }, []() {
    sendDcsCommand("CDU_X", "0");
    lastePressedStateCduAlpha = false;
  });

}

#endif
