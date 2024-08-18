#include "TftDisplay.h"
#include "CheckLists.h"
#include <MCUFRIEND_kbv.h>

/*
0: Main menu
    1: Preflight menu
        11: Cold
            111: Page 1
            112: Page 2
            113: Page 3
        12: Takeoff
        13: Hot flight
*/
int currentMenu = 0;

CheckLists::CheckLists(TftDisplay* _display) {
    display = _display;
}

void CheckLists::activate() {
    if (isActive == false) {
        printCurrentMenu();
    }
    isActive = true;
}

void CheckLists::deactivate() {
    isActive = false;
}

void CheckLists::clearScreen() {
    // Clear sub title
    display->clearRect(150, 0, 170, 30);
    // Clear content
    display->clearRect(0, 30, 320, 210);
}

void CheckLists::printMainMenu() {
    currentMenu = 0;
    printCurrentMenu();
}

void CheckLists::onPageChange(int page) {
    switch (currentMenu)
    {
    case 111:
        if (page == 2) {
            printPreFlightPage2();
            currentMenu = 112;
        }
        break;
    case 112:
        if (page == 1) {
            printPreFlightPage1();
            currentMenu = 111;
        }
        break;        
    
    case 121:
        if (page == 2) {
            printPreFlightPage2("h");
            currentMenu = 122;
        }
        break;
    case 122:
        if (page == 1) {
            printPreFlightPage1("h");
            currentMenu = 121;
        }
        break;        
    
    case 131:
        if (page == 2) {
            printPreFlightPage2("h");
            currentMenu = 132;
        }
        break;
    case 132:
        if (page == 1) {
            printPreFlightPage1("h");
            currentMenu = 131;
        }
        break;        
    default:
        break;
    }
}

void CheckLists::manageScreenBtn(const char* btn) {
switch (currentMenu)
    {
    case 0: // Current is Main menu
        if (btn == "t") {
            printPreStartup();
            currentMenu = 1;
        }
        break;
    case 1: // Current is pre-flight menu
        if (btn == "t") {
            printPreFlightPage1();
            currentMenu = 111; // Display first page (11 has no display)
        } else if (btn == "m") {
            printPreFlightPage1("h");
            currentMenu = 121;
        } else if (btn == "b") {
            printPreFlightPage1("a");
            currentMenu = 131;
        }
        break;
    case 111:
    case 112:
    case 113:
    case 121:
    case 122:
    case 123:
    case 131:
    case 132:
    case 133:
        printPreStartup();
        currentMenu = 1; // previous menu
        break;        
    default:
        break;
    }
}
void CheckLists::onTopScreenBtn() {
    manageScreenBtn("t");
}

void CheckLists::onMiddleScreenBtn() {
    manageScreenBtn("m");
}

void CheckLists::onBottomScreenBtn() {
    manageScreenBtn("b");
}

void CheckLists::printCurrentMenu() {
    clearScreen();
    switch (currentMenu) {
    case 0:
        display->print("Preflight", 10, 40, 2, TFT_DARKGREY);
        display->print("Startup", 10, 127, 2, TFT_DARKGREY);

        display->print("Landing", 235, 121, 2, TFT_DARKGREY);
        display->print("Shutdown", 223, 213, 2, TFT_DARKGREY);
        break;
    case 1: printPreStartup(); break;
    case 111: printPreFlightPage1(); break;
    case 112: printPreFlightPage2(); break;

    }
}

void CheckLists::printPreStartup() {
    clearScreen();
    // Sub title
    display->print("Pre flight", 180, 15, 2, TFT_CERULEAN_BLUE);

    display->print("Cold", 10, 40, 2, TFT_DARKGREY);
    display->print("Hot", 10, 127, 2, TFT_DARKGREY);
    display->print("Hot Air", 10, 203, 2, TFT_DARKGREY);
}

const char* CheckLists::getColdChar(const char* cold, const char* coldChar, const char* hotChar, const char* airChar) {
    if (cold == "") return coldChar;
    if (cold == "h") return hotChar;
    if (cold == "a") return airChar;
    return "";
}

void CheckLists::printPreFlightPage1(const char* cold = "") {
    clearScreen();
    display->print("PF Cold (1/2)", 140, 15, 2, TFT_CERULEAN_BLUE);

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

void CheckLists::printPreFlightPage2(const char* cold = "") {
    clearScreen();
    display->print("PF Cold (2/2)", 140, 15, 2, TFT_CERULEAN_BLUE);

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
