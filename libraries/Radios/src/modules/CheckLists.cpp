#include "TftDisplay.h"
#include "CheckLists.h"
#include <MCUFRIEND_kbv.h>

#include "checklists/mainmenu.h"
#include "checklists/preflight.h"
#include "checklists/startup.h"

/*
0: Main menu
    1: Preflight menu
        11: Cold
            111: Page 1
            112: Page 2
        12: Takeoff
            121: Page 1
            122: Page 2
        13: Hot flight
            131: Page 1
            132: Page 2
    2: Startup
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

void CheckLists::printMainMenu() {
    clPrintMainMenu(display, &currentMenu);
}

void CheckLists::onPageChange(int page) {
    switch (currentMenu)
    {
    case 111:
    case 121:
    case 131:
        if (page == 2) preFlightPrintPreFlightPage2(display, &currentMenu, (currentMenu == 111 ? "c" : (currentMenu == 121 ? "h" : "a")));
        break;
    case 112:
    case 122:
    case 132:
        if (page == 1) preFlightPrintPreFlightPage1(display, &currentMenu, (currentMenu == 112 ? "c" : (currentMenu == 122 ? "h" : "a")));
        break;
    default:
        break;
    }
}

void CheckLists::manageScreenBtn(const char* btn) {
switch (currentMenu)
    {
    case 0: // Current is Main menu
        // Top screen btn
        if (btn == "t") preFlightPrintMenu(display, &currentMenu);
        // middle screen btn
        else if (btn == "m") clPrintStartupPage1(display, &currentMenu);
        break;
    case 1: // Current is pre-flight menu
        if (btn == "t") preFlightPrintPreFlightPage1(display, &currentMenu, "c"); // 111
        else if (btn == "m") preFlightPrintPreFlightPage1(display, &currentMenu, "h"); // 121
        else if (btn == "b") preFlightPrintPreFlightPage1(display, &currentMenu, "a"); // 131
        break;
    case 111:
    case 112:
    case 121:
    case 122:
    case 131:
    case 132:
        preFlightPrintMenu(display, &currentMenu);
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
    display->clearChecklistScreen();
    switch (currentMenu) {
    case 0: clPrintMainMenu(display, &currentMenu); break;
    case 1: preFlightPrintMenu(display, &currentMenu); break;
    case 111: preFlightPrintPreFlightPage1(display, &currentMenu, "c"); break;
    case 112: preFlightPrintPreFlightPage2(display, &currentMenu, "c"); break;
    case 121: preFlightPrintPreFlightPage1(display, &currentMenu, "h"); break;
    case 122: preFlightPrintPreFlightPage2(display, &currentMenu, "h"); break;
    case 131: preFlightPrintPreFlightPage1(display, &currentMenu, "a"); break;
    case 132: preFlightPrintPreFlightPage2(display, &currentMenu, "a"); break;

    }
}
