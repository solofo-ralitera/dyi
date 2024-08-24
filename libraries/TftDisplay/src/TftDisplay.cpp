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

void TftDisplay::clearRect(int x, int y, int w, int h) {
    tft.fillRect(x, y, w, h, TFT_BLACK);
}

void TftDisplay::print(char *text, int col, int row, uint8_t size, int color, int bgColor = TFT_BLACK)
{
    tft.setTextSize(size);
    tft.setTextColor(color, bgColor);

    tft.setCursor(col, row);
    tft.println(text);
}

void TftDisplay::printRadioTitle(char *text) {
    print(text, 10, 13, 2, TFT_DARK_SPRING_GREEN);
}

void TftDisplay::printTRHelp(const char* text1, const char* text2) {
    print(text1, 200, 15, 2, TFT_DARKGREY);
    print(text2, 260, 15, 2, TFT_DARKGREY);
}

void TftDisplay::drawVolume(int volume) {
    tft.drawLine(260, 33, 320, 33, TFT_BLACK); // erase old indicator
    tft.drawLine(260, 33, (volume * 60 / 100) + 260, 33, TFT_DARKGREEN);
}

void TftDisplay::drawRadioSql(unsigned int sql) {
    tft.drawRect(197, 11, 39, 23, sql == 1 ? TFT_DARK_SPRING_GREEN : TFT_BLACK);
}

void TftDisplay::printBCHelp(const char* text) {
    print(text, 130, 220, 2, TFT_DARKGREY);
}

void TftDisplay::highLightBCHelp(unsigned int highlight) {
    tft.drawRect(125, 217, 57, 20, highlight == 1 ? TFT_DARK_SPRING_GREEN : TFT_BLACK);
}

void TftDisplay::printRadioChannel(char *text) {
    print(text, 120, 207, 4, TFT_DARK_SPRING_GREEN);
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

void TftDisplay::printIntercomCircle(int offsetX, int offsetY, unsigned int unmute) {
    tft.drawCircle(offsetX + 40, offsetY + 60, 25, unmute == 1 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);

}
void TftDisplay::printIntercomText(const char *text, int offsetX, int offsetY, unsigned int unmute) {
    print(text, offsetX + 23, offsetY + 50, 2, unmute == 1 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
}

void TftDisplay::printIntercomVolume(int offsetX, int offsetY, unsigned int volume, unsigned int unmute) {
    tft.drawLine(offsetX + 18, offsetY + 67, offsetX + 62, offsetY + 67, TFT_BLACK); // erase old indicator
    tft.drawLine(offsetX + 18, offsetY + 67, offsetX + 18 + (volume * 44 / 100), offsetY + 67, unmute == 1 ? TFT_DARK_SPRING_GREEN : TFT_DARKGREY);
}

void TftDisplay::clearChecklistScreen() {
    // Clear sub title
    clearRect(130, 0, 170, 30);
    // Clear content
    clearRect(0, 30, 320, 210);
}