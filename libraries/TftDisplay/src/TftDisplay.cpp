#include "Arduino.h"

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "Fonts/FreeSans9pt7b.h"

#include "TftDisplay.h"

// Don't forget to enable SUPPORT_8347D in MCUFRIEND_kbv.cpp
MCUFRIEND_kbv tft;


TftDisplay::TftDisplay()
{
}

void TftDisplay::begin() {
  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9481;
  tft.begin(ID);
  tft.setFont(&FreeSans9pt7b);
  clearScreen();
  tft.setRotation(1);
}

void TftDisplay::clearScreen() {
    tft.fillScreen(TFT_BLACK);
}

void TftDisplay::print(char *text, int col, int row, uint8_t size, int color, int bgColor = TFT_BLACK)
{
    tft.setTextSize(size);
    tft.setTextColor(color, bgColor);

    tft.setCursor(col, row);
    tft.println(text);
}

void TftDisplay::printRadioTitle(int activeIndex, char *text1, char *text2, char *text3, char *text4, char *text5) {
    tft.setFont();
    // Arc-210
    print(text1, 0, 13, activeIndex == 0 ? 2 : 1, TFT_DARKGREY);
    // UHF
    print(text2, 64, 13, activeIndex == 1 ? 2 : 1, TFT_DARKGREY);
    // VHF FM
    print(text3, 120, 13, activeIndex == 2 ? 2 : 1, TFT_DARKGREY);
    // ILS
    print(text4, 205, 13, activeIndex == 3 ? 2 : 1, TFT_DARKGREY);
    // TACAN
    print(text5, 256, 13, activeIndex == 4 ? 2 : 1, TFT_DARKGREY);

    tft.setFont(&FreeSans9pt7b);
}

void TftDisplay::printRadioChannel(char *text) {
    if (text != "") {
        // char buf[6];
        // strcpy(buf, "ch ");
        // strcat(buf, text);
        print(text, 120, 230, 3, TFT_DARK_SPRING_GREEN);
    } else {
        print("  ", 120, 230, 3, TFT_DARK_SPRING_GREEN);
    }
}

void TftDisplay::printRadioModulation(char *text) {
    print(text, 270, 112, 1, TFT_DARK_SPRING_GREEN);
}

void TftDisplay::printRadioFrequency(char *text) {
    print(text, 10, 110, 3, TFT_DARK_SPRING_GREEN);
}

void TftDisplay::printRadioSwitch(String switches[], unsigned int numSwitches, unsigned int selectedSwitch, int offsetPrint) {
    tft.setFont();
    for (unsigned int n = 0; n < numSwitches; n++) {
        int slen = switches[n].length() + 1;
        char buff[slen];
        switches[n].toCharArray(buff, slen);
        if (selectedSwitch == n) {
            print(buff, offsetPrint, 230 - (n * 10), 1, TFT_WHITE, TFT_DARK_SPRING_GREEN);
        } else {
            print(buff, offsetPrint, 230 - (n * 10), 1, TFT_DARKGREY);
        }
    }
    tft.setFont(&FreeSans9pt7b);
}