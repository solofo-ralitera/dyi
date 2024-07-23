#ifndef MatrixJoy_h
#define MatrixJoy_h

#include "Arduino.h"

class MatrixJoy
{
    public:
        MatrixJoy(
            byte* rows,
            byte* cols
        );

        byte btnStatus(int colIndex, int rowIndex);
    private:
        byte* rows;
        byte* cols;
        const int rowCount;
        const int colCount;
};

#endif

