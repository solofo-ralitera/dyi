#include "TftDisplay.h"
#include <MCUFRIEND_kbv.h>

void clPrintStartupPage1(TftDisplay* display, int* currentMenu) {
    display->clearChecklistScreen();
    display->print("Startup", 180, 15, 2, TFT_CERULEAN_BLUE);
    *currentMenu = 2;

}