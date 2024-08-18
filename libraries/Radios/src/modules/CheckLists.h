#ifndef checklist_h
#define checklist_h

#include "Arduino.h"
#include "TftDisplay.h"

class CheckLists {
    public:
        const char *title = "Checklists";
        bool isActive = false;

        CheckLists(TftDisplay*);

        void activate();
        void deactivate();

        void printMainMenu();
        void onPageChange(int page);
        void onTopScreenBtn();
        void onMiddleScreenBtn();
        void onBottomScreenBtn();
    private:
        TftDisplay* display;
        void clearScreen();
        void manageScreenBtn(const char* btn);
        void printCurrentMenu();
            void printPreStartup();
                // Preflight
                // cold = "": cold and dark start
                // colr = "h" hot start (eg takeoff)
                // cold = "a" air start
                void printPreFlightPage1(const char* cold = "");
                void printPreFlightPage2(const char* cold = "");

        const char* getColdChar(const char* cold, const char* coldChar, const char* hotChar, const char* airChar);
        
            
};

#endif