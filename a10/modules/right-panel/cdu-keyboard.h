#ifndef CduKeyboard_h
#define CduKeyboard_h

#include "Arduino.h"
#include "PushButton.h"


void setupCduKeyboard() {
  pinMode(A12, INPUT);
}

bool lastePressedState = false;

void runCduKeyboard() {

  static int numSampleCduLsk = 0;
  static int samplesCduLsk[ANALOG_SAMPLE];
  static int analogMeanCduLsk = 0;
  int aRead = analogRead(A12);
  PushButton::getPBCode(aRead, &numSampleCduLsk, samplesCduLsk, &analogMeanCduLsk, 612, 616);

  if (lastePressedState == false && analogMeanCduLsk == 0 &&  aRead != 0) {
    return;
  }

  // set state as pressed 
  lastePressedState = true;

  static PushButton cduLsk1;
  cduLsk1.runCallBack((analogMeanCduLsk >= 595 && analogMeanCduLsk <= 599 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_3L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_3L", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk2;
  cduLsk2.runCallBack((analogMeanCduLsk >= 684 && analogMeanCduLsk <= 688 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_5L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_5L", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk3;
  cduLsk3.runCallBack((analogMeanCduLsk >= 804 && analogMeanCduLsk <= 808 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_7L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_7L", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk4;
  cduLsk4.runCallBack((analogMeanCduLsk >= 1020 && analogMeanCduLsk <= 1025 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_9L", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_9L", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk5;
  cduLsk5.runCallBack((analogMeanCduLsk >= 510 && analogMeanCduLsk <= 514 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_3R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_3R", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk6;
  cduLsk6.runCallBack((analogMeanCduLsk >= 411 && analogMeanCduLsk <= 415 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_5R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_5R", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk7;
  cduLsk7.runCallBack((analogMeanCduLsk >= 268 && analogMeanCduLsk <= 272 ) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_7R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_7R", "0");
    lastePressedState = false;
  });

  static PushButton cduLsk8;
  cduLsk8.runCallBack((analogMeanCduLsk == 0 && aRead == 0) ? 0 : 1, []() {
    sendDcsCommand("CDU_LSK_9R", "1");
  }, []() {
    sendDcsCommand("CDU_LSK_9R", "0");
    lastePressedState = false;
  });
}

#endif
