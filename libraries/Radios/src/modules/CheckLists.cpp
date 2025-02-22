#include "TftDisplay.h"
#include "CheckLists.h"
#include <MCUFRIEND_kbv.h>

#include "checklists/mainmenu.h"
#include "checklists/fuel.h"
#include "checklists/nvg.h"

/*
0: Main menu
1: Fuel
2: NVG (night vision goggles)
*/
int clCurrentMenu = 0;

Fuel fuel;
Nvg nvg;

unsigned long refreshMillis = millis();

void fuelPrint(TftDisplay* display, int* clCurrentMenu) {
    display->clearChecklistScreen();
    // Sub title
    display->print("FUEL", 130, 15, 2, TFT_WHITE);
    *clCurrentMenu = 1;
    fuel.print(display);
}

void nvgPrint(TftDisplay* display, int* clCurrentMenu) {
    display->clearChecklistScreen();
    // Sub title
    display->print("NVGs", 130, 15, 2, TFT_WHITE);
    *clCurrentMenu = 2;
    nvg.print(display);
}

CheckLists::CheckLists(TftDisplay* _display) {
    display = _display;
    
}

int CheckLists::getCurrentMenu() {
    return clCurrentMenu;
}

void CheckLists::activate(int* currentRadioMenu) {
    if (isActive == false) {
        printCurrentMenu();
    }
    setRadioMenu(currentRadioMenu);
    isActive = true;
}

void CheckLists::setRadioMenu(int* currentRadioMenu) {
    switch (clCurrentMenu) {
        case 0: *currentRadioMenu = 6; break; // main menu
        case 1: *currentRadioMenu = 61; break; // fuel screen
        case 2: *currentRadioMenu = 62; break;  // nvg screen
        default: break;
    }
}

void CheckLists::deactivate() {
    isActive = false;
}

void CheckLists::printMainMenu() {
    clPrintMainMenu(display, &clCurrentMenu);
}

void CheckLists::onPageChange(int page) {
    switch (clCurrentMenu)
    {
        case 111:
        case 121:
        case 131:
        case 112:
        case 122:
        case 132:
        default:
            break;
    }
}

void CheckLists::manageScreenBtn(const char* btn) {
switch (clCurrentMenu)
    {
    case 0: // Current is Main menu
        // Top screen btn
        if (btn == "t") fuelPrint(display, &clCurrentMenu);
        else if (btn == "m") nvgPrint(display, &clCurrentMenu);
        // else if (btn == "b") checkAllLeds();
        break;
    case 1: // Current is pre-flight menu
    case 111:
    case 112:
    case 121:
    case 122:
    case 131:
    case 132:
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

void CheckLists::onBottomScreenBtn(LedMatrix* ledMatrix) {
    manageScreenBtn("b");
    if (clCurrentMenu == 0) {
        ledMatrix->checkAll();
    }
}

void CheckLists::printCurrentMenu() {
    display->clearChecklistScreen();
    switch (clCurrentMenu) {
        case 0: clPrintMainMenu(display, &clCurrentMenu); break;
        case 1: fuelPrint(display, &clCurrentMenu); break;
        case 2: nvgPrint(display, &clCurrentMenu); break;
        default: break;
    }
}

void CheckLists::refreshScreen() {
    if (isActive == false) return;
    unsigned long currentMillis = millis();
    if (currentMillis - refreshMillis > 1500) {
        switch (clCurrentMenu) {
            // List all refresh case here
            case 1: fuel.print(display); break;
            default: break;
        }
        refreshMillis = currentMillis;
    }
}

void CheckLists::setFuel100(unsigned int f) {
    fuel.f100 = f;
}
void CheckLists::setFuel1000(unsigned int f) {
    fuel.f1000 = f;
}
void CheckLists::setFuel10000(unsigned int f) {
    fuel.f10000 = f;
}
void CheckLists::setFuelFlowL(unsigned int f) {
    fuel.fFlowL = f;
}
void CheckLists::setFuelFlowR(unsigned int f) {
    fuel.fFlowR = f;
}