#ifndef SlaveModule_h
#define SlaveModule_h

#include "Arduino.h"
#include <Joystick.h>
#include <Wire.h>

#define CMD_BTN 0
#define CMD_X_AXIS 1
#define CMD_Y_AXIS 2
#define CMD_Z_AXIS 3
#define CMD_RX_AXIS 4
#define CMD_RY_AXIS 5
#define CMD_RZ_AXIS 6
#define CMD_RUDDER_AXIS 7
#define CMD_THROTTLE_AXIS 8
#define CMD_ACCELERATOR_AXIS 9
#define CMD_BRAKE_AXIS 10
#define CMD_STEERING_AXIS 11

class SlaveModule
{
    public:
        SlaveModule(
            int i2CAddress, // Adresse I2C du module
            int i2CBufferSize, // Taille en bytes (octets) des données envoyé par le module
            int numberOfFirstButton, // numero du premier boutton du module
            int _numberOfButtons, // Nombre de bouttons (joystick) du module
            /*
            Type de commande pour chaque bytes de data I2C
            All axes has a range of 0-255
               Value for each byte is CMD_XXX
            */
            int *lasteDataI2CConfig
        );

        void readModule(
            Joystick_* joystick
        );

        void setBitAsJoystickStatus(
            Joystick_ *joystick,         
            byte bitValue,
            int bitPosition
        );
    private:
        int i2CAddress;
        int i2CBufferSize;
        int numberOfFirstButton;
        int numberOfButtons;
        uint32_t lastButtonsState[8]; // max 64 buttons per module
        int *lasteDataI2CConfig;
};

#endif

