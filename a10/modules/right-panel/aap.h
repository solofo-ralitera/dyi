#ifndef aap_h
#define aap_h

#include "Arduino.h"
#include "PushButton.h"


void setupAap() {
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);

  pinMode(22, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
}

int currentSteerPt = -1;
int currentAapPage = -1;
void runAap() {
  // ROTARY STEER PT
  int a10 = analogRead(A10);
  // Flt plan 325
  if (currentSteerPt != 0 && a10 >= 320 && a10 <= 330) {
    sendDcsCommand("AAP_STEERPT", "0");
    currentSteerPt = 0;
  }
  // Mark 511
  else if (currentSteerPt != 1 && a10 >= 500 && a10 <= 520) {
    sendDcsCommand("AAP_STEERPT", "1");
    currentSteerPt = 1;
  }
  // 0 Mission
  else if (currentSteerPt != 2 && a10 == 0) {
    sendDcsCommand("AAP_STEERPT", "2");
    currentSteerPt = 2;
  }

  // ROTARY PAGE
  int a11 = analogRead(A11);
  // Other 511
  if (currentAapPage != 0 && a11 >= 501 && a11 <= 521) {
    sendDcsCommand("AAP_PAGE", "0");
    currentAapPage = 0;
  }
  // Position 374
  else if (currentAapPage != 1 && a11 >= 364 && a11 <= 384) {
    sendDcsCommand("AAP_PAGE", "1");
    currentAapPage = 1;
  }
  // steer 202
  else if (currentAapPage != 2 && a11 >= 192 && a11 <= 212) {
    sendDcsCommand("AAP_PAGE", "2");
    currentAapPage = 2;
  }
  // waypt 309
  else if (currentAapPage != 3 && a11 >= 299 && a11 <= 319) {
    sendDcsCommand("AAP_PAGE", "3");
    currentAapPage = 3;
  }

  // SWITCH STEER
  // Steer up
  static PushButton pin22;
  pin22.runCallBack(bitRead(PINA, PINA0), []() {
    sendDcsCommand("AAP_STEER", "2");
  }, []() {
    sendDcsCommand("AAP_STEER", "1");
  });
  // Steer down
  static PushButton pin24;
  pin24.runCallBack(bitRead(PINA, PINA2), []() {
    sendDcsCommand("AAP_STEER", "0");
  }, []() {
    sendDcsCommand("AAP_STEER", "1");
  });

  // SWITCH CDU/EGI
  // CDU
  static PushButton pin26;
  pin26.runCallBack(bitRead(PINA, PINA4), []() {
    sendDcsCommand("AAP_CDUPWR", "1");
  }, []() {
    sendDcsCommand("AAP_CDUPWR", "0");
  });

  // EGI
  static PushButton pin28;
  pin28.runCallBack(bitRead(PINA, PINA6), []() {
    sendDcsCommand("AAP_EGIPWR", "1");
  }, []() {
    sendDcsCommand("AAP_EGIPWR", "0");
  });
}

#endif