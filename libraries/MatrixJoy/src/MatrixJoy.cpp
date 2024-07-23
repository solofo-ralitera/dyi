#include "Arduino.h"
#include "MatrixJoy.h"

static void OUTPUTa1( void ) { bitSet(DDRC, DDC1); }
static void INPUTa1( void ) { bitClear(DDRC, DDC1); }


MatrixJoy::MatrixJoy(byte* r, byte* c):
rowCount(sizeof(rows) / sizeof(rows[0])),
colCount(sizeof(cols) / sizeof(cols[0]))
{
    rows = r;
    cols = c;

    for(int x=0; x<rowCount; x++) {
        pinMode(rows[x], INPUT);
    }

    for (int x=0; x<colCount; x++) {
        pinMode(cols[x], INPUT_PULLUP);
    }
}

byte MatrixJoy::btnStatus(int colIndex, int rowIndex) {
    pinMode(cols[colIndex], OUTPUT);
    digitalWrite(cols[colIndex], LOW);

    pinMode(rows[rowIndex], INPUT_PULLUP);
    byte status = digitalRead(rows[rowIndex]);
    pinMode(rows[rowIndex], INPUT);

	pinMode(cols[colIndex], INPUT);

    //0 => bouton appuyé, 1 => relaché (car en pullup)
    Serial.println(status);
    return status;
}
