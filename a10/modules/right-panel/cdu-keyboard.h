#ifndef CduKeyboard_h
#define CduKeyboard_h

#include "Arduino.h"
#include "PushButton.h"


void setupCduKeyboard() {
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  pinMode(A14, INPUT);
  pinMode(A15, INPUT);
}

void runCduKeyboard() {
  
  static int numSampleCduOther = 0;
  static int samplesCduOther[ANALOG_SAMPLE];
  static int analogMeanCduOther = 0;
  PushButton::getPBCode(analogRead(A14), &numSampleCduOther, samplesCduOther, &analogMeanCduOther, 407, 411);

  static int numSampleCduNum = 0;
  static int samplesCduNum[ANALOG_SAMPLE];
  static int analogMeanCduNum = 0;
  PushButton::getPBCode(analogRead(A15), &numSampleCduNum, samplesCduNum, &analogMeanCduNum, 147, 149);

  static int numSampleCduAlpha = 0;
  static int samplesCduAlpha[ANALOG_SAMPLE];
  static int analogMeanCduAlpha = 0;
  PushButton::getPBCode(analogRead(A13), &numSampleCduAlpha, samplesCduAlpha, &analogMeanCduAlpha, 407, 411);

  static int numSampleCduLsk = 0;
  static int samplesCduLsk[ANALOG_SAMPLE];
  static int analogMeanCduLsk = 0;
  PushButton::getPBCode(analogRead(A12), &numSampleCduLsk, samplesCduLsk, &analogMeanCduLsk, 612, 616);

  static PushButton cduLsk1;
  cduLsk1.runCallBack((analogMeanCduLsk >= 595 && analogMeanCduLsk <= 599 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_3L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_3L", "0");
  });

  static PushButton cduLsk2;
  cduLsk2.runCallBack((analogMeanCduLsk >= 684 && analogMeanCduLsk <= 688 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_5L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_5L", "0");
  });

  static PushButton cduLsk3;
  cduLsk3.runCallBack((analogMeanCduLsk >= 804 && analogMeanCduLsk <= 808 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_7L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_7L", "0");
  });

  static PushButton cduLsk4;
  cduLsk4.runCallBack((analogMeanCduLsk >= 1020 && analogMeanCduLsk <= 1025 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_9L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_9L", "0");
  });

  static PushButton cduLsk5;
  cduLsk5.runCallBack((analogMeanCduLsk >= 510 && analogMeanCduLsk <= 514 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_3R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_3R", "0");
  });

  static PushButton cduLsk6;
  cduLsk6.runCallBack((analogMeanCduLsk >= 411 && analogMeanCduLsk <= 415 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_5R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_5R", "0");
  });

  static PushButton cduLsk7;
  cduLsk7.runCallBack((analogMeanCduLsk >= 268 && analogMeanCduLsk <= 272 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_7R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_7R", "0");
  });

  static PushButton cduLsk8;
  cduLsk8.runCallBack((analogMeanCduLsk == 0 &&  analogRead(A12) == 0) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_9R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_9R", "0");
  });

  ///////////////////////////////////////////////////////////////////////

  static PushButton cduNum0;
  cduNum0.runCallBack((analogMeanCduNum >= 122 && analogMeanCduNum <= 124 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_0", "1");
  }, []() {
    sendDcsCommand("CDU_0", "0");
  });

  static PushButton cduNum1;
  cduNum1.runCallBack((analogMeanCduNum >= 216 && analogMeanCduNum <= 220 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_1", "1");
  }, []() {
    sendDcsCommand("CDU_1", "0");
  });

  static PushButton cduNum2;
  cduNum2.runCallBack((analogMeanCduNum >= 207 && analogMeanCduNum <= 211 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_2", "1");
  }, []() {
    sendDcsCommand("CDU_2", "0");
  });  

  static PushButton cduNum3;
  cduNum3.runCallBack((analogMeanCduNum >= 199 && analogMeanCduNum <= 203 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_3", "1");
  }, []() {
    sendDcsCommand("CDU_3", "0");
  });  

  static PushButton cduNum4;
  cduNum4.runCallBack((analogMeanCduNum >= 178 && analogMeanCduNum <= 182 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_4", "1");
  }, []() {
    sendDcsCommand("CDU_4", "0");
  });  

  static PushButton cduNum5;
  cduNum5.runCallBack((analogMeanCduNum >= 185 && analogMeanCduNum <= 189 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_5", "1");
  }, []() {
    sendDcsCommand("CDU_5", "0");
  });  

  static PushButton cduNum6;
  cduNum6.runCallBack((analogMeanCduNum >= 191 && analogMeanCduNum <= 195 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_6", "1");
  }, []() {
    sendDcsCommand("CDU_6", "0");
  });  

  static PushButton cduNum7;
  cduNum7.runCallBack((analogMeanCduNum >= 171 && analogMeanCduNum <= 175 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_7", "1");
  }, []() {
    sendDcsCommand("CDU_7", "0");
  });  

  static PushButton cduNum8;
  cduNum8.runCallBack((analogMeanCduNum >= 164 && analogMeanCduNum <= 168 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_8", "1");
  }, []() {
    sendDcsCommand("CDU_8", "0");
  });  

  static PushButton cduNum9;
  cduNum9.runCallBack((analogMeanCduNum >= 159 && analogMeanCduNum <= 163 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_9", "1");
  }, []() {
    sendDcsCommand("CDU_9", "0");
  });  

  static PushButton cduNumDot;
  cduNumDot.runCallBack((analogMeanCduNum >= 76 && analogMeanCduNum <= 80 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_POINT", "1");
  }, []() {
    sendDcsCommand("CDU_POINT", "0");
  });

  static PushButton cduNumSlash;
  cduNumSlash.runCallBack((analogMeanCduNum >= 142 && analogMeanCduNum <= 146 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_SLASH", "1");
  }, []() {
    sendDcsCommand("CDU_SLASH", "0");
  });

  static PushButton cduSys;
  cduSys.runCallBack((analogMeanCduNum >= 227 && analogMeanCduNum <= 231 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_SYS", "1");
  }, []() {
    sendDcsCommand("CDU_SYS", "0");
  });  

  static PushButton cduNav;
  cduNav.runCallBack((analogMeanCduNum >= 241 && analogMeanCduNum <= 245 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_NAV", "1");
  }, []() {
    sendDcsCommand("CDU_NAV", "0");
  }); 

  static PushButton cduWp;
  cduWp.runCallBack((analogMeanCduNum >= 261 && analogMeanCduNum <= 264 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_WP", "1");
  }, []() {
    sendDcsCommand("CDU_WP", "0");
  }); 

  static PushButton cduOset;
  cduOset.runCallBack((analogMeanCduNum >= 286 && analogMeanCduNum <= 290 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_OSET", "1");
  }, []() {
    sendDcsCommand("CDU_OSET", "0");
  }); 

  static PushButton cduFpm;
  cduFpm.runCallBack((analogMeanCduNum >= 326 && analogMeanCduNum <= 330 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_FPM", "1");
  }, []() {
    sendDcsCommand("CDU_FPM", "0");
  }); 

  static PushButton cduPrev;
  cduPrev.runCallBack((analogMeanCduNum >= 394 && analogMeanCduNum <= 398 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_PREV", "1");
  }, []() {
    sendDcsCommand("CDU_PREV", "0");
  });

  static PushButton cduDim;
  cduDim.runCallBack((analogMeanCduNum >= 535 && analogMeanCduNum <= 539 ) ? 0 : 1, []() {
    // TODO physical brt
  }, []() {
    // TODO physical brt
  });

  static PushButton cduBrt;
  cduDim.runCallBack((analogMeanCduNum >= 1000 && analogMeanCduNum <= 1024 ) ? 0 : 1, []() {
    // TODO physical brt
  }, []() {
    // TODO physical brt
  });

  static PushButton cduA;
  cduA.runCallBack((analogMeanCduAlpha >= 556 && analogMeanCduAlpha <= 560 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_A", "1");
  }, []() {
    sendDcsCommand("CDU_A", "0");
  });

  static PushButton cduB;
  cduB.runCallBack((analogMeanCduAlpha >= 590 && analogMeanCduAlpha <= 594 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_B", "1");
  }, []() {
    sendDcsCommand("CDU_B", "0");
  });

  static PushButton cduC;
  cduC.runCallBack((analogMeanCduAlpha >= 636 && analogMeanCduAlpha <= 640 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_C", "1");
  }, []() {
    sendDcsCommand("CDU_C", "0");
  });

  static PushButton cduD;
  cduD.runCallBack((analogMeanCduAlpha >= 703 && analogMeanCduAlpha <= 707 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_D", "1");
  }, []() {
    sendDcsCommand("CDU_D", "0");
  });

  static PushButton cduE;
  cduE.runCallBack((analogMeanCduAlpha >= 812 && analogMeanCduAlpha <= 816 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_E", "1");
  }, []() {
    sendDcsCommand("CDU_E", "0");
  });

  static PushButton cduF;
  cduF.runCallBack((analogMeanCduAlpha >= 1020 && analogMeanCduAlpha <= 1025 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_F", "1");
  }, []() {
    sendDcsCommand("CDU_F", "0");
  });

  static PushButton cduG;
  cduG.runCallBack((analogMeanCduAlpha >= 530 && analogMeanCduAlpha <= 534 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_G", "1");
  }, []() {
    sendDcsCommand("CDU_G", "0");
  });

  static PushButton cduH;
  cduH.runCallBack((analogMeanCduAlpha >= 508 && analogMeanCduAlpha <= 512 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_H", "1");
  }, []() {
    sendDcsCommand("CDU_H", "0");
  });

  static PushButton cduI;
  cduI.runCallBack((analogMeanCduAlpha >= 490 && analogMeanCduAlpha <= 494 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_I", "1");
  }, []() {
    sendDcsCommand("CDU_I", "0");
  });

  static PushButton cduJ;
  cduJ.runCallBack((analogMeanCduAlpha >= 474 && analogMeanCduAlpha <= 478 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_J", "1");
  }, []() {
    sendDcsCommand("CDU_J", "0");
  });

  static PushButton cduK;
  cduK.runCallBack((analogMeanCduAlpha >= 460 && analogMeanCduAlpha <= 464 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_K", "1");
  }, []() {
    sendDcsCommand("CDU_K", "0");
  });

  static PushButton cduL;
  cduL.runCallBack((analogMeanCduAlpha >= 447 && analogMeanCduAlpha <= 451 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_L", "1");
  }, []() {
    sendDcsCommand("CDU_L", "0");
  });

  static PushButton cduM;
  cduM.runCallBack((analogMeanCduAlpha >= 354 && analogMeanCduAlpha <= 358 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_M", "1");
  }, []() {
    sendDcsCommand("CDU_M", "0");
  });

  static PushButton cduN;
  cduN.runCallBack((analogMeanCduAlpha >= 371 && analogMeanCduAlpha <= 375 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_N", "1");
  }, []() {
    sendDcsCommand("CDU_N", "0");
  });

  static PushButton cduO;
  cduO.runCallBack((analogMeanCduAlpha >= 386 && analogMeanCduAlpha <= 390 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_O", "1");
  }, []() {
    sendDcsCommand("CDU_O", "0");
  });

  static PushButton cduP;
  cduP.runCallBack((analogMeanCduAlpha >= 400 && analogMeanCduAlpha <= 404 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_P", "1");
  }, []() {
    sendDcsCommand("CDU_P", "0");
  });

  static PushButton cduQ;
  cduQ.runCallBack((analogMeanCduAlpha >= 422 && analogMeanCduAlpha <= 426 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_Q", "1");
  }, []() {
    sendDcsCommand("CDU_Q", "0");
  });

  static PushButton cduR;
  cduR.runCallBack((analogMeanCduAlpha >= 435 && analogMeanCduAlpha <= 438 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_R", "1");
  }, []() {
    sendDcsCommand("CDU_R", "0");
  });

  static PushButton cduS;
  cduS.runCallBack((analogMeanCduAlpha >= 332 && analogMeanCduAlpha <= 336 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_S", "1");
  }, []() {
    sendDcsCommand("CDU_S", "0");
  });

  static PushButton cduT;
  cduT.runCallBack((analogMeanCduAlpha >= 306 && analogMeanCduAlpha <= 310 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_T", "1");
  }, []() {
    sendDcsCommand("CDU_T", "0");
  });

  static PushButton cduU;
  cduU.runCallBack((analogMeanCduAlpha >= 271 && analogMeanCduAlpha <= 275) ? 0 : 1, []() {
    sendDcsCommand("CDU_U", "1");
  }, []() {
    sendDcsCommand("CDU_U", "0");
  });

  static PushButton cduV;
  cduV.runCallBack((analogMeanCduAlpha >= 219 && analogMeanCduAlpha <= 223) ? 0 : 1, []() {
    sendDcsCommand("CDU_V", "1");
  }, []() {
    sendDcsCommand("CDU_V", "0");
  });

  static PushButton cduW;
  cduW.runCallBack((analogMeanCduAlpha >= 136 && analogMeanCduAlpha <= 140) ? 0 : 1, []() {
    sendDcsCommand("CDU_W", "1");
  }, []() {
    sendDcsCommand("CDU_W", "0");
  });

  static PushButton cduX;
  cduX.runCallBack((analogMeanCduAlpha >= 57 && analogMeanCduAlpha <= 61) ? 0 : 1, []() {
    sendDcsCommand("CDU_X", "1");
  }, []() {
    sendDcsCommand("CDU_X", "0");
  });

  static PushButton cduPup;
  cduPup.runCallBack((analogMeanCduOther >= 448 && analogMeanCduOther <= 452) ? 0 : 1, []() {
    sendDcsCommand("CDU_PG", "2");
  }, []() {
    sendDcsCommand("CDU_PG", "1");
  });

  static PushButton cduPdown;
  cduPdown.runCallBack((analogMeanCduOther >= 419 && analogMeanCduOther <= 423) ? 0 : 1, []() {
    sendDcsCommand("CDU_PG", "0");
  }, []() {
    sendDcsCommand("CDU_PG", "1");
  });

  static PushButton cduOtherPoint;
  cduOtherPoint.runCallBack((analogMeanCduOther >= 478 && analogMeanCduOther <= 482) ? 0 : 1, []() {
    // No function
  }, []() {
    // No function
  });

  static PushButton cduMk;
  cduMk.runCallBack((analogMeanCduOther >= 391 && analogMeanCduOther <= 393) ? 0 : 1, []() {
    sendDcsCommand("CDU_MK", "1");
  }, []() {
    sendDcsCommand("CDU_MK", "0");
  });

  static PushButton cduOtherBlank;
  cduOtherBlank.runCallBack((analogMeanCduOther >= 512 && analogMeanCduOther <= 516) ? 0 : 1, []() {
    // No function
  }, []() {
    // No function
  });

  static PushButton cduBck;
  cduBck.runCallBack((analogMeanCduOther >= 552 && analogMeanCduOther <= 556) ? 0 : 1, []() {
    sendDcsCommand("CDU_BCK", "1");
  }, []() {
    sendDcsCommand("CDU_BCK", "0");
  });

  static PushButton cduSpc;
  cduSpc.runCallBack((analogMeanCduOther >= 604 && analogMeanCduOther <= 608) ? 0 : 1, []() {
    sendDcsCommand("CDU_SPC", "1");
  }, []() {
    sendDcsCommand("CDU_SPC", "0");
  });  

  static PushButton cduScrollDown;
  cduScrollDown.runCallBack((analogMeanCduOther >= 388 && analogMeanCduOther <= 390) ? 0 : 1, []() {
    sendDcsCommand("CDU_SCROLL", "0");
  }, []() {
    sendDcsCommand("CDU_SCROLL", "1");
  });

  static PushButton cduScrollUp;
  cduScrollUp.runCallBack((analogMeanCduOther >= 353 && analogMeanCduOther <= 357) ? 0 : 1, []() {
    sendDcsCommand("CDU_SCROLL", "2");
  }, []() {
    sendDcsCommand("CDU_SCROLL", "1");
  });  

  static PushButton cduY;
  cduY.runCallBack((analogMeanCduOther >= 678 && analogMeanCduOther <= 682) ? 0 : 1, []() {
    sendDcsCommand("CDU_Y", "1");
  }, []() {
    sendDcsCommand("CDU_Y", "0");
  });

  static PushButton cduZ;
  cduZ.runCallBack((analogMeanCduOther >= 795 && analogMeanCduOther <= 799) ? 0 : 1, []() {
    sendDcsCommand("CDU_Z", "1");
  }, []() {
    sendDcsCommand("CDU_Z", "0");
  });

  static PushButton cduClr;
  cduClr.runCallBack((analogMeanCduOther >= 311 && analogMeanCduOther <= 315) ? 0 : 1, []() {
    sendDcsCommand("CDU_CLR", "1");
  }, []() {
    sendDcsCommand("CDU_CLR", "0");
  });

  static PushButton cduFa;
  cduFa.runCallBack((analogMeanCduOther >= 254 && analogMeanCduOther <= 258) ? 0 : 1, []() {
    sendDcsCommand("CDU_FA", "1");
  }, []() {
    sendDcsCommand("CDU_FA", "0");
  });

  static PushButton cduDataUp;
  cduDataUp.runCallBack((analogMeanCduOther >= 1020 && analogMeanCduOther <= 1025) ? 0 : 1, []() {
    sendDcsCommand("CDU_DATA", "2");
  }, []() {
    sendDcsCommand("CDU_DATA", "1");
  });

  static PushButton cduDataDown;
  cduDataDown.runCallBack((analogMeanCduOther >= 165 && analogMeanCduOther <= 169) ? 0 : 1, []() {
    sendDcsCommand("CDU_DATA", "0");
  }, []() {
    sendDcsCommand("CDU_DATA", "1");
  });
}

#endif
