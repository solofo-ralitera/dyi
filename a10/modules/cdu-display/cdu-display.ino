#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

#define	TFT_DARK_SPRING_GREEN   0x1B88

#define DCSBIOS_IRQ_SERIAL
// #define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

// Don't forget to enable SUPPORT_8347D in MCUFRIEND_kbv.cpp
MCUFRIEND_kbv tft;

String line0 = "                    ";
String line1 = "                    ";
String line2 = "                    ";
String line3 = "                    ";
String line4 = "                    ";
String line5 = "                    ";
String line6 = "                    ";
String line7 = "                    ";
String line8 = "                    ";
String line9 = "                    ";

void clearScreen() {
    tft.fillScreen(TFT_BLACK);
}

void printCdu(char *text, int row)
{
  switch(row) {
    case 0:
      if (strcmp(line0.c_str(), text) == 0) return;
    case 1:
      if (strcmp(line1.c_str(), text) == 0) return;
    case 2:
      if (strcmp(line2.c_str(), text) == 0) return;
    case 3:
      if (strcmp(line3.c_str(), text) == 0) return;
    case 4:
      if (strcmp(line4.c_str(), text) == 0) return;
    case 5:
      if (strcmp(line5.c_str(), text) == 0) return;
    case 6:
      if (strcmp(line6.c_str(), text) == 0) return;
    case 7:
      if (strcmp(line7.c_str(), text) == 0) return;
    case 8:
      if (strcmp(line8.c_str(), text) == 0) return;
    case 9:
      if (strcmp(line9.c_str(), text) == 0) return;
    default:
      break;
  }
  for (int i = 0; i <= 24; i++) {
    switch(row) {
      case 0:
        if (line0.charAt(i) == text[i]) continue;
        line0.setCharAt(i, text[i]);
        break;
      case 1:
        if (line1.charAt(i) == text[i]) continue;
        line1.setCharAt(i, text[i]);
        break;
      case 2:
        if (line2.charAt(i) == text[i]) continue;
        line2.setCharAt(i, text[i]);
        break;
      case 3:
        if (line3.charAt(i) == text[i]) continue;
        line3.setCharAt(i, text[i]);
        break;
      case 4:
        if (line4.charAt(i) == text[i]) continue;
        line4.setCharAt(i, text[i]);
        break;
      case 5:
        if (line5.charAt(i) == text[i]) continue;
        line5.setCharAt(i, text[i]);
        break;
      case 6:
        if (line6.charAt(i) == text[i]) continue;
        line6.setCharAt(i, text[i]);
        break;
      case 7:
        if (line7.charAt(i) == text[i]) continue;
        line7.setCharAt(i, text[i]);
        break;
      case 8:
        if (line8.charAt(i) == text[i]) continue;
        line8.setCharAt(i, text[i]);
        break;
      case 9:
        if (line9.charAt(i) == text[i]) continue;
        line9.setCharAt(i, text[i]);
        break;
      default:
        break;
    }
    tft.setCursor((i * 13), 10 + (row * 23));
    tft.print(text[i]);
  }
}

// CDU
DcsBios::StringBuffer<24> cduLine0Buffer(A_10C_CDU_LINE0, [](char* newValue) {
  printCdu(newValue, 0);
});
DcsBios::StringBuffer<24> cduLine1Buffer(A_10C_CDU_LINE1, [](char* newValue) {
  printCdu(newValue, 1);
});
DcsBios::StringBuffer<24> cduLine2Buffer(A_10C_CDU_LINE2, [](char* newValue) {
  printCdu(newValue, 2);
});
DcsBios::StringBuffer<24> cduLine3Buffer(A_10C_CDU_LINE3, [](char* newValue) {
  printCdu(newValue, 3);
});
DcsBios::StringBuffer<24> cduLine4Buffer(A_10C_CDU_LINE4, [](char* newValue) {
  printCdu(newValue, 4);
});
DcsBios::StringBuffer<24> cduLine5Buffer(A_10C_CDU_LINE5, [](char* newValue) {
  printCdu(newValue, 5);
});
DcsBios::StringBuffer<24> cduLine6Buffer(A_10C_CDU_LINE6, [](char* newValue) {
  printCdu(newValue, 6);
});
DcsBios::StringBuffer<24> cduLine7Buffer(A_10C_CDU_LINE7, [](char* newValue) {
  printCdu(newValue, 7);
});
DcsBios::StringBuffer<24> cduLine8Buffer(A_10C_CDU_LINE8, [](char* newValue) {
  printCdu(newValue, 8);
});
DcsBios::StringBuffer<24> cduLine9Buffer(A_10C_CDU_LINE9, [](char* newValue) {
  printCdu(newValue, 9);
});

void setup() {
  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9481;
  tft.begin(ID);
  clearScreen();
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setRotation(1);

  DcsBios::setup();
}

void loop(void) {
  DcsBios::loop();
}