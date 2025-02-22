#ifndef checklistnvg_h
#define checklistnvg_h

#include "TftDisplay.h"
#include <MCUFRIEND_kbv.h>

class Nvg {
    public:
        Nvg() {
        }

        print(TftDisplay* display) {
            display->printBCHelp("- Toggle +");
        }
        
    private:
};


#endif

