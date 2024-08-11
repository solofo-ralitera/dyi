/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
// #define DCSBIOS_IRQ_SERIAL
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

// DcsBios::RotaryEncoder arc10Mhz("ARC210_100MHZ_SEL", "DEC", "INC", 22, 23);
DcsBios::ActionButton arc210FskUpToggle("ARC210_FSK_UP", "TOGGLE", 22);

void setup() {
  DcsBios::setup();

}

void loop() {
  // DcsBios::loop();

  while(!DcsBios::tryToSendDcsBiosMessage("ARC210_FSK_UP", "1"));
  while(!DcsBios::tryToSendDcsBiosMessage("ARC210_FSK_UP 1", ""));
  delay(1000);
  while(!DcsBios::tryToSendDcsBiosMessage("ARC210_FSK_UP", "0"));
  while(!DcsBios::tryToSendDcsBiosMessage("ARC210_FSK_UP 0", ""));
  delay(1000);
}
