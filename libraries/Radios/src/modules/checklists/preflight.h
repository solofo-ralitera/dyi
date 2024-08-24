#include "TftDisplay.h"
#include <MCUFRIEND_kbv.h>


const char* getColdChar(const char* cold, const char* coldChar, const char* hotChar, const char* airChar) {
    if (cold == "") return coldChar;
    if (cold == "h") return hotChar;
    if (cold == "a") return airChar;
    return "";
}

void preFlightPrintMenu(TftDisplay* display, int* currentMenu) {
    display->clearChecklistScreen();
    // Sub title
    display->print("Pre flight", 180, 15, 2, TFT_CERULEAN_BLUE);
    *currentMenu = 1;

    display->print("Cold", 10, 40, 2, TFT_DARKGREY);
    display->print("Hot", 10, 127, 2, TFT_DARKGREY);
    display->print("Hot Air", 10, 203, 2, TFT_DARKGREY);
}

void preFlightPrintSubTitle(TftDisplay* display, int currentPage, const char* cold) {
    char buffer[13];
    sprintf(buffer, "PF %s (%d/2)", (cold == "" ? "Cold" : (cold == "h" ? "Hot" : "Air")), currentPage);

    if (cold == "c") display->print(buffer, 140, 15, 2, TFT_CERULEAN_BLUE);
    else if (cold == "h") display->print(buffer, 140, 15, 2, TFT_CERULEAN_BLUE);
    else if (cold == "a") display->print(buffer, 140, 15, 2, TFT_CERULEAN_BLUE);
}

void preFlightPrintPreFlightPage1(TftDisplay* display, int* currentMenu, const char* cold) {
    display->clearChecklistScreen();
    preFlightPrintSubTitle(display, 1, cold);

    if (cold == "c") *currentMenu = 111;
    else if(cold == "h") *currentMenu = 121;
    else if(cold == "a") *currentMenu = 131;

    display->print("LASTE", 0, 40, 2, TFT_CERULEAN_BLUE);
        display->print("AP", 20, 60, 2, TFT_DARKGREY);
            display->print("-", 46, 60, 2, TFT_ORANGE);
        
        display->print("RDR", 75, 60, 2, TFT_DARKGREY);
            display->print("T", 116, 60, 2, TFT_ORANGE);
        
        display->print("EAC", 150, 60, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "T", "T"), 190, 60, 2, TFT_ORANGE);

    display->print("Power CTRL / Throttle / SAS", 0, 80, 2, TFT_CERULEAN_BLUE);
        display->print("BATT PWR", 0, 100, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "T", "T"), 105, 100, 2, TFT_ORANGE);

        display->print("L/R AC GEN", 135, 100, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "T", "T"), 265, 100, 2, TFT_ORANGE);

        display->print("APU", 20, 120, 2, TFT_DARKGREY);
            display->print("B", 63, 120, 2, TFT_ORANGE);

        display->print("INV", 100, 120, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "-", "T", "T"), 140, 120, 2, TFT_ORANGE);

        // Throttle
        display->print("APU", 0, 140, 2, TFT_DARKGREY);
            display->print("OFF", 50, 140, 2, TFT_ORANGE);

        display->print("L/R Eng Oper", 100, 140, 2, TFT_DARKGREY);
            display->print("-", 250, 140, 2, TFT_ORANGE);

        display->print("ENG Fuel flow", 20, 160, 2, TFT_DARKGREY);
            display->print("T", 180, 160, 2, TFT_ORANGE);

        // SAS
        display->print("SAS Monit", 0, 180, 2, TFT_CERULEAN_BLUE);
            display->print("-", 110, 180, 2, TFT_ORANGE);

    display->print("AUX", 0, 200, 2, TFT_CERULEAN_BLUE);
        display->print("HARS/SAS", 50, 200, 2, TFT_DARKGREY);
            display->print("B", 150, 200, 2, TFT_ORANGE);

        display->print("NGH VIS", 200, 200, 2, TFT_DARKGREY);
            display->print("B", 300, 200, 2, TFT_ORANGE);

    display->print("Gear", 0, 220, 2, TFT_CERULEAN_BLUE);
        display->print("SKID", 60, 220, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "T", "T"), 115, 220, 2, TFT_ORANGE);

        display->print("LTS", 145, 220, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "-", "T", "T"), 184, 220, 2, TFT_ORANGE);

        display->print("Gear", 220, 220, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "B", "T"), 275, 220, 2, TFT_ORANGE);
}

void preFlightPrintPreFlightPage2(TftDisplay* display, int* currentMenu, const char* cold) {
    display->clearChecklistScreen();

    preFlightPrintSubTitle(display, 2, cold);
    if(cold == "c") *currentMenu = 112;
    else if(cold == "h") *currentMenu = 122;
    else if(cold == "a") *currentMenu = 132;

    display->print("AHCP", 0, 40, 2, TFT_CERULEAN_BLUE);
        display->print("Master Arm", 0, 60, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "-", "-", "T"), 123, 60, 2, TFT_ORANGE);

        display->print("GUN PAC", 160, 60, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "-", "T"), 250, 60, 2, TFT_ORANGE);

        display->print("Laser", 0, 80, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "-", "-", "T"), 63, 80, 2, TFT_ORANGE);

        display->print("TGP", 100, 80, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "B", "T"), 145, 80, 2, TFT_ORANGE);

        display->print("Next three", 0, 100, 2, TFT_DARKGREY);
            display->print("T", 130, 100, 2, TFT_ORANGE);

        display->print("Last three", 170, 100, 2, TFT_DARKGREY);
            display->print(getColdChar(cold, "B", "T", "T"), 295, 100, 2, TFT_ORANGE);

    display->print("Fuel", 0, 120, 2, TFT_CERULEAN_BLUE);
        display->print("All EXT/TK", 0, 140, 2, TFT_DARKGREY);
            display->print("B", 130, 140, 2, TFT_ORANGE);

        display->print("All BOOST T", 170, 140, 2, TFT_DARKGREY);
            display->print("T", 290, 140, 2, TFT_ORANGE);

        display->print("All FILL", 0, 160, 2, TFT_DARKGREY);
            display->print("PUSH", 100, 160, 2, TFT_ORANGE);

        display->print("Lever", 190, 160, 2, TFT_DARKGREY);
            display->print("UP", 255, 160, 2, TFT_ORANGE);
}
