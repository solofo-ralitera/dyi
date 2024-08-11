/*
Gestion des radios Arc10, Com, UHF, ILS, Tacan
*/
#ifndef radio_h
#define radio_h

#define PB_TOP_SCREEN 1020
#define PB_MIDDLE_SCREEN 500
#define PB_BOTTOM_SCREEN 340
#define PB_FREQUENCY_SELECTOR_1 260
#define PB_FREQUENCY_SELECTOR_2 210
#define PB_MASTER_MODE 178
#define PB_CHANNEL 158
#define PB_FREQUENCY_SELECTOR_3 140
#define PB_FREQUENCY_SELECTOR_4 127
#define PB_FREQUENCY_SELECTOR_5 115
#define PB_SECONDARY_MODE 105
#define PB_MOD_SELECTOR 97
#define PB_OFFSET 90
#define PB_AMFM 82
#define PB_VOLUME 75
#define PB_SQL 68
#define PB_MENU 48
#define PB_XMTRCV 12

int getPBCode(int analogValue) {
  // Serial.println(analogValue);
  if (analogValue > 30 && analogValue < 37) return 0; // No press (32 à cause du pullup)
  if (analogValue > PB_TOP_SCREEN) return PB_TOP_SCREEN;
  if (analogValue > PB_TOP_SCREEN) return PB_TOP_SCREEN;
  if (analogValue > PB_MIDDLE_SCREEN) return PB_MIDDLE_SCREEN;
  if (analogValue > PB_BOTTOM_SCREEN) return PB_BOTTOM_SCREEN;
  if (analogValue > PB_FREQUENCY_SELECTOR_1) return PB_FREQUENCY_SELECTOR_1;
  if (analogValue > PB_FREQUENCY_SELECTOR_2) return PB_FREQUENCY_SELECTOR_2;
  if (analogValue > PB_MASTER_MODE) return PB_MASTER_MODE;
  if (analogValue > PB_CHANNEL) return PB_CHANNEL;
  if (analogValue > PB_FREQUENCY_SELECTOR_3) return PB_FREQUENCY_SELECTOR_3;
  if (analogValue > PB_FREQUENCY_SELECTOR_4) return PB_FREQUENCY_SELECTOR_4;
  if (analogValue > PB_FREQUENCY_SELECTOR_5) return PB_FREQUENCY_SELECTOR_5;
  if (analogValue > PB_SECONDARY_MODE) return PB_SECONDARY_MODE;
  if (analogValue > PB_MOD_SELECTOR) return PB_MOD_SELECTOR;
  if (analogValue > PB_OFFSET) return PB_OFFSET;
  if (analogValue > PB_AMFM) return PB_AMFM;
  if (analogValue > PB_VOLUME) return PB_VOLUME;
  if (analogValue > PB_SQL) return PB_SQL;
  if (analogValue > PB_MENU) return PB_MENU;
  if (analogValue > PB_XMTRCV) return PB_XMTRCV;
}

#endif

