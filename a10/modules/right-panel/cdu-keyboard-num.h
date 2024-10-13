#ifndef CduKeyboardNum_h
#define CduKeyboardNum_h

#include "Arduino.h"
#include "PushButton.h"


void setupCduKeyboardNum() {
  pinMode(A15, INPUT);
}

bool lastePressedStateCduNum = false;

void runCduKeyboardNum() {

  static int numSampleCduNum = 0;
  static int samplesCduNum[ANALOG_SAMPLE];
  static int analogMeanCduNum = 0;
  PushButton::getPBCode(analogRead(A15), &numSampleCduNum, samplesCduNum, &analogMeanCduNum, 147, 149);
  
  if (lastePressedStateCduNum == false && analogMeanCduNum == 0) {
    return;
  }

  lastePressedStateCduNum = true;

  static PushButton cduNum0;
  cduNum0.runCallBack((analogMeanCduNum >= 122 && analogMeanCduNum <= 124 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_0", "1");
  }, []() {
    sendDcsCommand("CDU_0", "0");
    lastePressedStateCduNum = false;
  });

  static PushButton cduNum1;
  cduNum1.runCallBack((analogMeanCduNum >= 216 && analogMeanCduNum <= 220 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_1", "1");
  }, []() {
    sendDcsCommand("CDU_1", "0");
    lastePressedStateCduNum = false;
  });

  static PushButton cduNum2;
  cduNum2.runCallBack((analogMeanCduNum >= 207 && analogMeanCduNum <= 211 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_2", "1");
  }, []() {
    sendDcsCommand("CDU_2", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum3;
  cduNum3.runCallBack((analogMeanCduNum >= 199 && analogMeanCduNum <= 203 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_3", "1");
  }, []() {
    sendDcsCommand("CDU_3", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum4;
  cduNum4.runCallBack((analogMeanCduNum >= 178 && analogMeanCduNum <= 182 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_4", "1");
  }, []() {
    sendDcsCommand("CDU_4", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum5;
  cduNum5.runCallBack((analogMeanCduNum >= 185 && analogMeanCduNum <= 189 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_5", "1");
  }, []() {
    sendDcsCommand("CDU_5", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum6;
  cduNum6.runCallBack((analogMeanCduNum >= 191 && analogMeanCduNum <= 195 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_6", "1");
  }, []() {
    sendDcsCommand("CDU_6", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum7;
  cduNum7.runCallBack((analogMeanCduNum >= 171 && analogMeanCduNum <= 175 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_7", "1");
  }, []() {
    sendDcsCommand("CDU_7", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum8;
  cduNum8.runCallBack((analogMeanCduNum >= 164 && analogMeanCduNum <= 168 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_8", "1");
  }, []() {
    sendDcsCommand("CDU_8", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNum9;
  cduNum9.runCallBack((analogMeanCduNum >= 159 && analogMeanCduNum <= 163 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_9", "1");
  }, []() {
    sendDcsCommand("CDU_9", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNumDot;
  cduNumDot.runCallBack((analogMeanCduNum >= 76 && analogMeanCduNum <= 80 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_POINT", "1");
  }, []() {
    sendDcsCommand("CDU_POINT", "0");
    lastePressedStateCduNum = false;
  });

  static PushButton cduNumSlash;
  cduNumSlash.runCallBack((analogMeanCduNum >= 142 && analogMeanCduNum <= 146 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_SLASH", "1");
  }, []() {
    sendDcsCommand("CDU_SLASH", "0");
    lastePressedStateCduNum = false;
  });

  static PushButton cduSys;
  cduSys.runCallBack((analogMeanCduNum >= 227 && analogMeanCduNum <= 231 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_SYS", "1");
  }, []() {
    sendDcsCommand("CDU_SYS", "0");
    lastePressedStateCduNum = false;
  });  

  static PushButton cduNav;
  cduNav.runCallBack((analogMeanCduNum >= 241 && analogMeanCduNum <= 245 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_NAV", "1");
  }, []() {
    sendDcsCommand("CDU_NAV", "0");
    lastePressedStateCduNum = false;
  }); 

  static PushButton cduWp;
  cduWp.runCallBack((analogMeanCduNum >= 261 && analogMeanCduNum <= 264 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_WP", "1");
  }, []() {
    sendDcsCommand("CDU_WP", "0");
    lastePressedStateCduNum = false;
  }); 

  static PushButton cduOset;
  cduOset.runCallBack((analogMeanCduNum >= 286 && analogMeanCduNum <= 290 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_OSET", "1");
  }, []() {
    sendDcsCommand("CDU_OSET", "0");
    lastePressedStateCduNum = false;
  }); 

  static PushButton cduFpm;
  cduFpm.runCallBack((analogMeanCduNum >= 326 && analogMeanCduNum <= 330 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_FPM", "1");
  }, []() {
    sendDcsCommand("CDU_FPM", "0");
    lastePressedStateCduNum = false;
  }); 

  static PushButton cduPrev;
  cduPrev.runCallBack((analogMeanCduNum >= 394 && analogMeanCduNum <= 398 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_PREV", "1");
  }, []() {
    sendDcsCommand("CDU_PREV", "0");
    lastePressedStateCduNum = false;
  });

  static PushButton cduDim;
  cduDim.runCallBack((analogMeanCduNum >= 535 && analogMeanCduNum <= 539 ) ? 0 : 1, []() {
    // TODO physical brt
  }, []() {
    // TODO physical brt
    lastePressedStateCduNum = false;
  });

  static PushButton cduBrt;
  cduDim.runCallBack((analogMeanCduNum >= 1000 && analogMeanCduNum <= 1024 ) ? 0 : 1, []() {
    // TODO physical brt
  }, []() {
    // TODO physical brt
    lastePressedStateCduNum = false;
  });
}

#endif
