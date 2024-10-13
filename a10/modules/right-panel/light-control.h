#ifndef LightControl_h
#define LightControl_h

#include "Arduino.h"

#include "PushButton.h"
#include "AutoReleaseSwitch.h"
#include "KnobJoy.h"

void setupLightControl() {
    pinMode(30, INPUT_PULLUP);
    pinMode(31, INPUT_PULLUP);
    pinMode(32, INPUT_PULLUP);
    pinMode(33, INPUT_PULLUP);
    pinMode(34, INPUT_PULLUP);
    pinMode(35, INPUT_PULLUP);
    pinMode(36, INPUT_PULLUP);
    pinMode(37, INPUT_PULLUP);
    pinMode(38, INPUT_PULLUP);
    pinMode(39, INPUT_PULLUP);
    pinMode(40, INPUT_PULLUP);
    pinMode(41, INPUT_PULLUP);
    pinMode(42, INPUT_PULLUP);
    pinMode(43, INPUT_PULLUP);
    pinMode(44, INPUT_PULLUP);
    pinMode(45, INPUT_PULLUP);
    pinMode(46, INPUT_PULLUP);
    pinMode(47, INPUT_PULLUP);
    pinMode(48, INPUT_PULLUP);
}

void runLightControl() {
  // Positon Flash: PINL7
  static PushButton pin42;
  pin42.runCallBack(bitRead(PINL, PINL7), []() {
    sendDcsCommand("LCP_POSITION", "2");
  }, []() {
    sendDcsCommand("LCP_POSITION", "1");
  });

  // Positon Steady: PINL6
  static PushButton pin43;
  pin43.runCallBack(bitRead(PINL, PINL6), []() {
    sendDcsCommand("LCP_POSITION", "0");
  }, []() {
    sendDcsCommand("LCP_POSITION", "1");
  });

  // Formation click: PING2
  // TODO toogle pinky

  // Formation: PING1 / PING0
  static KnobJoy pin4041(I2C_DATA, 40, 41);
  pin4041.runCallBack([]() {
    sendDcsCommand("LCP_FORMATION", "+1500");
  }, []() {
    sendDcsCommand("LCP_FORMATION", "-1500");
  });

  // Anti collision: PIND7
  static PushButton pin38;
  pin38.runCallBack(bitRead(PIND, PIND7), []() {
    sendDcsCommand("LCP_ANTICOLLISION", "1");
  }, []() {
    sendDcsCommand("LCP_ANTICOLLISION", "0");
  });

  // Eng Inst: PINL5 / PINL4
  static KnobJoy pin4445(I2C_DATA, 45, 44);
  pin4445.runCallBack([]() {
    sendDcsCommand("LCP_ENG_INST", "+1500");
  }, []() {
    sendDcsCommand("LCP_ENG_INST", "-1500");
  });

  // NOSE ILLUM: PINC0
  static PushButton pin37;
  pin37.runCallBack(bitRead(PINC, PINC0), []() {
    sendDcsCommand("LCP_NOSE_ILLUM", "1");
  }, []() {
    sendDcsCommand("LCP_NOSE_ILLUM", "0");
  });

  // AUX INST: PINC3 / PINC4
  static KnobJoy pin3334(I2C_DATA, 34, 33);
  pin3334.runCallBack([]() {
    sendDcsCommand("LCP_AUX_INST", "+1500");
  }, []() {
    sendDcsCommand("LCP_AUX_INST", "-1500");
  });

  // Signal lts Brt: PINL3
  static PushButton pin46;
  pin46.runCallBack(bitRead(PINL, PINL3), []() {
    sendDcsCommand("LCP_SIGNAL_LIGHTS", "1");
  }, []() {
    sendDcsCommand("LCP_SIGNAL_LIGHTS", "0");
  });

  // FLT INST: PINC1 / PINC2
  static KnobJoy pin3536(I2C_DATA, 35, 36);
  pin3536.runCallBack([]() {
    sendDcsCommand("LCP_FLIGHT_INST", "+1500");
  }, []() {
    sendDcsCommand("LCP_FLIGHT_INST", "-1500");
  });

  // ACCEL & COMP: PINC5
  static PushButton pin32;
  pin32.runCallBack(bitRead(PINC, PINC5), []() {
    sendDcsCommand("LCP_ACCEL_COMP", "1");
  }, []() {
    sendDcsCommand("LCP_ACCEL_COMP", "0");
  });

  // Flood: PINL2 / PINL1
  static KnobJoy pin4748(I2C_DATA, 47, 48);
  pin4748.runCallBack([]() {
    sendDcsCommand("LCP_FLOOD", "+1500");
  }, []() {
    sendDcsCommand("LCP_FLOOD", "-1500");
  });

  // CONSOLE: PINC6 / PINC7
  static KnobJoy pin3031(I2C_DATA, 30, 31);
  pin3031.runCallBack([]() {
    sendDcsCommand("LCP_CONSOLE", "+1500");
  }, []() {
    sendDcsCommand("LCP_CONSOLE", "-1500");
  });

  // Serial.println(bitRead(PING, PING2));

}
#endif
