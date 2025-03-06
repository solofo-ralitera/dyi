#ifndef KnobJoyEsp32_h
#define KnobJoyEsp32_h

#include "Arduino.h"
#include <ESP32Encoder.h>


// Delay between position change (millis)
#define CHANGE_POSITION_DELAY 100
// Number of position change before triggering joystick press
#define CHANGE_POSITION_BUFFER 3

class KnobJoyEsp32
{
  public:
    KnobJoyEsp32(
      int pinLeft,
      int pinRight
    );
    
    void runCallBack(
      void (*leftCallback)(),
      void (*rightCallback)()
    );
  private:
    ESP32Encoder knob;
    unsigned long _previousMillis;
    long oldPosition;
    bool checkForRelease;
};

#endif

