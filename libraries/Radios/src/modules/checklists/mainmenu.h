#include "TftDisplay.h"
#include <MCUFRIEND_kbv.h>

void clPrintMainMenu(TftDisplay* display, int *currentMenu) {
    display->clearChecklistScreen();
    *currentMenu = 0;
    
    display->print("Fuel", 10, 40, 2, TFT_WHITE);
    display->print("Nvg", 10, 127, 2, TFT_WHITE);

    display->print("LEDs", 10, 210, 2, TFT_WHITE);

    // display->print("Landing", 235, 121, 2, TFT_DARKGREY);
    // display->print("Shutdown", 223, 213, 2, TFT_DARKGREY);
}