#ifndef checklistfuel_h
#define checklistfuel_h

#include "TftDisplay.h"
#include <MCUFRIEND_kbv.h>

class Fuel {
    public:
        unsigned int f100 = 0;
        unsigned int f1000 = 0;
        unsigned int f10000 = 0;
        unsigned int fFlowL = 0;
        unsigned int fFlowR = 0;

        Fuel() {
        }

        print(TftDisplay* display) {
            display->printBCHelp("test");

            // Qty in lbs
            unsigned long fQuantity = f100 + f1000 + f10000;
            char buffFQuantity[6];
            sprintf(buffFQuantity, "%6u ", fQuantity);
            String fQte = String(buffFQuantity);
            fQte.concat("Lbs");
            display->print(fQte.c_str(), 10, 50, 2, TFT_WHITE);

            // flow: lbs (or pounds) per hour
            unsigned long fLow = (fFlowL + fFlowR);

            // in seconds
            unsigned long durationLeft = 3600 * fQuantity / fLow;
            int hrs = durationLeft / 3600;
            int mins = (durationLeft - (hrs * 3600)) / 60;  

            display->print("  ", 10, 80, 2, TFT_WHITE);
            display->print(String(hrs).substring(0, 2).c_str(), 10, 80, 2, TFT_WHITE);
            display->print("h", 40, 80, 2, TFT_WHITE);
            display->print("  ", 60, 80, 2, TFT_WHITE);
            display->print(String(mins).substring(0, 2).c_str(), 60, 80, 2, TFT_WHITE);
            display->print("m", 100, 80, 2, TFT_WHITE);



        }
        
    private:
};


#endif

