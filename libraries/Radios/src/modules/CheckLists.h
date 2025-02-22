#ifndef checklist_h
#define checklist_h

#include "Arduino.h"
#include "TftDisplay.h"
#include "checklists/fuel.h"
#include "ledMatrix.h"


class CheckLists {
    public:
        const char *title = "Sys";
        bool isActive = false;

        CheckLists(TftDisplay*);

        void activate(int* currentRadioMenu);
        void deactivate();

        void printMainMenu();
        int getCurrentMenu();
        void onPageChange(int page);
        void onTopScreenBtn();
        void onMiddleScreenBtn();
        void onBottomScreenBtn(LedMatrix*);

        void refreshScreen();
        void setRadioMenu(int* currentRadioMenu);
        
        void setFuel100(unsigned int);
        void setFuel1000(unsigned int);
        void setFuel10000(unsigned int);
        void setFuelFlowL(unsigned int);
        void setFuelFlowR(unsigned int);

    private:
        TftDisplay* display;
        void clearScreen();
        void manageScreenBtn(const char* btn);
        void printCurrentMenu();
        void printStartup();
        
            
};

#endif