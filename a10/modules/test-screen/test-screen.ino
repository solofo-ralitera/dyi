#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
// Enable SUPPORT_8347D in MCUFRIEND_kbv.cpp
MCUFRIEND_kbv tft;

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void) {
  // Serial.begin(9600);

  uint16_t ID = tft.readID(); //
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  tft.begin(ID);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
}

void printmsg(const char *text, int col, int row, uint8_t size)
{
    tft.setTextSize(size);
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(col, row);
    tft.println(text);
}

void loop(void) {
  printmsg("Hello", 10, 10, 2);
}
