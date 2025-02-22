#ifndef electricalPowerPanel_h
#define electricalPowerPanel_h

#include "PushButton.h"

void initElectricalPowerPanel() {
  pinMode(14, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(50, INPUT_PULLUP);
}

void batteryPwrOn() {
    radios.sendDcsCommand("EPP_BATTERY_PWR", "1");
}
void batteryPwrOff() {
    radios.sendDcsCommand("EPP_BATTERY_PWR", "0");
}

void inverterStby() {
    radios.sendDcsCommand("EPP_INVERTER", "2");
}
void inverterOff() {
    radios.sendDcsCommand("EPP_INVERTER", "1");
}
void inverterTest() {
    radios.sendDcsCommand("EPP_INVERTER", "0");
}

void apcGenRPower() {
    radios.sendDcsCommand("EPP_AC_GEN_PWR_R", "1");
}
void apcGenROff() {
    radios.sendDcsCommand("EPP_AC_GEN_PWR_R", "0");
}

void apcGenLPower() {
    radios.sendDcsCommand("EPP_AC_GEN_PWR_L", "1");
}
void apcGenLOff() {
    radios.sendDcsCommand("EPP_AC_GEN_PWR_L", "0");
}

void apcGenPower() {
    radios.sendDcsCommand("EPP_APU_GEN_PWR", "1");
}
void apcGenOff() {
    radios.sendDcsCommand("EPP_APU_GEN_PWR", "0");
}


void runElectricalPowerPanel() {
  // 14 Battery PWR
  static PushButton batteryPwr;
  batteryPwr.runCallBack(bitRead(PINJ, PINJ1), batteryPwrOn, batteryPwrOff);

  // 45 Emer FLOOD
  // bitRead(PINL, PINL4);
  // Do nothing, may be physical led?

  // 46 Inverter STBY
  static PushButton inverterSTBY;
  inverterSTBY.runCallBack(bitRead(PINL, PINL3), inverterStby, inverterOff);
  // 47 Inverter TEST
  static PushButton inverterTEST;
  inverterTEST.runCallBack(bitRead(PINL, PINL2), inverterTest, inverterOff);
  
  // 48 AC GEN PWR R
  static PushButton acGenPwrR;
  acGenPwrR.runCallBack(bitRead(PINL, PINL1), apcGenRPower, apcGenROff);

  // 50 AC GEN PWR L
  static PushButton acGenPwrL;
  acGenPwrL.runCallBack(bitRead(PINB, PINB3), apcGenLPower,apcGenLOff);

  // 49 APU GEN PWR
  static PushButton apuGenPwr;
  apuGenPwr.runCallBack(bitRead(PINL, PINL0), apcGenPower, apcGenOff);
}
#endif

