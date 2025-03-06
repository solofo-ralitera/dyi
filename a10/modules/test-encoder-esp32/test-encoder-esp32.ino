#include "KnobJoyEsp32.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(34, INPUT_PULLUP);
  // digitalWrite(34, LOW);

  pinMode(35, INPUT_PULLUP);
  // digitalWrite(35, LOW);

  // ESP32Encoder::useInternalWeakPullResistors = puType::up;
}

void loop() {
  // static KnobJoyEsp32 modSelector(33, 25);
  static KnobJoyEsp32 modSelector(35, 34);
  modSelector.runCallBack([]() {
    Serial.println("Left");
  }, []() {
    Serial.println("Right");
  });
}
