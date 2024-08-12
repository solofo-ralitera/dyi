#include "Arduino.h"

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

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
    // Arc-210
    print(text1, 0, 13, activeIndex == 0 ? 2 : 1, activeIndex == 0 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
    // UHF
    print(text2, 64, 13, activeIndex == 1 ? 2 : 1, activeIndex == 1 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
    // VHF FM
    print(text3, 120, 13, activeIndex == 2 ? 2 : 1, activeIndex == 2 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
    // ILS
    print(text4, 205, 13, activeIndex == 3 ? 2 : 1, activeIndex == 3 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
    // TACAN
    print(text5, 256, 13, activeIndex == 4 ? 2 : 1, activeIndex == 4 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
}

void TftDisplay::printTRHelp(const char* text1, const char* text2) {
    print(text1, 250, 35, 1, TFT_DARKGREY);
    print(text2, 290, 35, 1, TFT_DARKGREY);
}

void TftDisplay::drawVolume(int volume) {
    tft.drawLine(290, 45, 320, 45, TFT_BLACK); // erase old indicator
    tft.drawLine(290, 45, (volume * 30 / 100) + 290, 45, TFT_DARKGREEN);
}

void TftDisplay::drawRadioSql(unsigned int sql) {
    tft.drawRect(247, 33, 23, 13, sql == 1 ? TFT_DARK_SPRING_GREEN : TFT_BLACK);
}

void TftDisplay::printBCHelp(const char* text) {
    print(text, 130, 220, 1, TFT_DARKGREY);
}

void TftDisplay::drawTacanTest(unsigned int test) {
    tft.drawRect(125, 219, 33, 15, test == 1 ? TFT_DARK_SPRING_GREEN : TFT_BLACK);
}

void TftDisplay::printRadioChannel(char *text) {
    print(text, 120, 180, 4, TFT_DARK_SPRING_GREEN);
    /* if (text != "") {
        // char buf[6];
        // strcpy(buf, "ch ");
        // strcat(buf, text);
        print(text, 120, 230, 3, TFT_DARK_SPRING_GREEN);
    } else {
        print("  ", 120, 230, 3, TFT_DARK_SPRING_GREEN);
    } */
}

void TftDisplay::printRadioModulation(char *text) {
    print(text, 270, 60, 4, TFT_DARK_SPRING_GREEN);
}

void TftDisplay::printRadioFrequency(char *text) {
    // tft.fillRect(20, 40, 100, 100, TFT_BLACK);
    print(text, 40, 50, 5, TFT_DARK_SPRING_GREEN);
}

void TftDisplay::printRadioSwitch(String switches[], unsigned int numSwitches, unsigned int selectedSwitch, int offsetPrint) {
    for (unsigned int n = 0; n < numSwitches; n++) {
        int slen = switches[n].length() + 1;
        char buff[slen];
        switches[n].toCharArray(buff, slen);
        if (selectedSwitch == n) {
            print(buff, offsetPrint, 220 - (n * 18), 2, TFT_WHITE, TFT_DARK_SPRING_GREEN);
        } else {
            print(buff, offsetPrint, 220 - (n * 18), 2, TFT_DARKGREY);
        }
    }
}
