/*
Gestion des radios Arc10, Com, UHF, ILS, Tacan
*/
#ifndef TftDisplay_h
#define TftDisplay_h

#include "Arduino.h"
#include <MCUFRIEND_kbv.h>

// https://github.com/newdigate/rgb565_colors?tab=readme-ov-file#green
#define	TFT_CERULEAN_BLUE    0x2A97
#define	TFT_DARK_SPRING_GREEN   0x1B88
#define	TFT_BATTLESHIP_GRAY   0x8430

class TftDisplay
{
  public:
    TftDisplay();
    void begin();
    void print(char *text, int col, int row, uint8_t size, int color, int bgColor = TFT_BLACK);

    void clearScreen();
    void clearRect(int x, int y, int w, int h);
    
    void printRadioTitle(char *text);
    void printTRHelp(const char* text1, const char* text2);

    void printBCHelp(const char* text1);
    void highLightBCHelp(unsigned int highlight);

    void printRadioChannel(char* text);
    void printRadioFrequency(char *text);
    void printRadioModulation(char *text);
    void printRadioSwitch(String switches[], unsigned int numSwitch, unsigned int selectedSwitch, int offsetPrint);
    void drawVolume(int volume);
    void drawRadioSql(unsigned int sql);

    void printIntercomCircle(int offsetX, int offsetY, unsigned int unmute);
    void printIntercomText(const char *text, int offsetX, int offsetY, unsigned int unmute);
    void printIntercomVolume(int offsetX, int offsetY, unsigned int volume, unsigned int unmute);

    void clearChecklistScreen();
};

#endif

