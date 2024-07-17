#ifndef MasterModule_h
#define MasterModule_h

#include "Arduino.h"

class MasterModule
{
  public:
    MasterModule();

    void setBitAsJoystickStatus(
      byte bitValue,
      int firstButtonNumber,
      uint32_t *lastButtonsState,
      int bitPosition
    );
};

#endif

