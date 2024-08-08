/*
Gestion des radios Arc10, Com, UHF, ILS, Tacan
*/
#ifndef TftDisplay_h
#define TftDisplay_h

#include "Arduino.h"

// https://github.com/newdigate/rgb565_colors?tab=readme-ov-file#green
#define	TFT_CERULEAN_BLUE    0x2A97
#define	TFT_DARK_SPRING_GREEN   0x1B88

class TftDisplay
{
  public:
    TftDisplay();
    void begin();
    void print(char *text, int col, int row, uint8_t size, int color, int bgColor);

    void clearScreen();
    void printRadioTitle(int activeIndex, char *text1, char *text2, char *text3, char *text4, char *text5);
    void printRadioChannel(char* text);
    void printRadioFrequency(char *text);
    void printRadioModulation(char *text);
    void printRadioSwitch(String switches[], unsigned int numSwitch, unsigned int selectedSwitch, int offsetPrint);
};

#endif

