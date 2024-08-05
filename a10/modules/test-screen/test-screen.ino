/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
#define DCSBIOS_IRQ_SERIAL
// #define DCSBIOS_DEFAULT_SERIAL

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "DcsBios.h"
#include "internal/Addresses.h"

// Don't forget to enable SUPPORT_8347D in MCUFRIEND_kbv.cpp
MCUFRIEND_kbv tft;

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void printmsg(const char *text, int col, int row, uint8_t size)
{
    tft.setTextSize(size);
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(col, row);
    tft.println(text);
}

void onArc210ActiveChannelChange(char* newValue) {
  printmsg(newValue, 10, 30, 2);
}
void onArc210FrequencyChange(char* newValue) {
  printmsg(newValue, 10, 60, 3);
}


DcsBios::StringBuffer<2> arc210ActiveChannelBuffer(A_10C_ARC210_ACTIVE_CHANNEL_ADDR, onArc210ActiveChannelChange);
DcsBios::StringBuffer<7> arc210FrequencyBuffer(A_10C_ARC210_FREQUENCY_ADDR, onArc210FrequencyChange);
void setup(void) {
  uint16_t ID = tft.readID(); //
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  tft.begin(ID);
  tft.fillScreen(BLACK);
  tft.setRotation(1);

  DcsBios::setup();
}

void loop(void) {
  DcsBios::loop();
  printmsg("Hello", 10, 10, 2);

}
