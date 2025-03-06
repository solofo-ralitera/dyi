#include "Arduino.h"
#include "KnobJoyEsp32.h"
#include <ESP32Encoder.h>

KnobJoyEsp32::KnobJoyEsp32(
  int pinLeft,
  int pinRight
) {
  //ESP32Encoder::useInternalWeakPullResistors = puType::down;
	// Enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  
  knob.attachFullQuad(pinLeft, pinRight);
  oldPosition = 0;
  _previousMillis = 0;
  checkForRelease = false;
}

void KnobJoyEsp32::runCallBack(void (*leftCallback)(), void (*rightCallback)()) {
  long newPosition = (int32_t) knob.getCount();

  if (abs(newPosition - oldPosition) > CHANGE_POSITION_BUFFER) {
    if (newPosition > oldPosition) {
      // Turn left
      // Serial.println("left");
      leftCallback();
    } else if (newPosition < oldPosition) {
      // Turn right
      // Serial.println("right");
      rightCallback();
    }
    oldPosition = newPosition;
  }
}
