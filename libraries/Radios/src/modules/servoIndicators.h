#ifndef servoIndicators_h
#define servoIndicators_h

#include <Servo.h>

Servo flapsIndicator;

void servoIndicatorsInit() {
    flapsIndicator.attach(14);
    flapsIndicator.write(180);
}

void servoIndicatosSetFlaps(unsigned int intValue) {
  flapsIndicator.write(map(intValue, 0, 65535, 180, 100));
}

#endif

