#ifndef servoIndicators_h
#define servoIndicators_h

#include <Servo_Hardware_PWM.h>

Servo flapsIndicator;

void servoIndicatorsInit() {
    flapsIndicator.attach(44);
    flapsIndicator.write(180);
}

void servoIndicatosSetFlaps(unsigned int intValue) {
  flapsIndicator.write(map(intValue, 0, 65535, 180, 100));
}

#endif

