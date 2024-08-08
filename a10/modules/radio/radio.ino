#include <Wire.h>
#include "PushButton.h"
#include "AutoReleaseSwitch.h"
#include "KnobJoy.h"
#include "Radios.h"

// Adresse I2C du module
#define I2C_ADDRESS 5
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 3
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
};

// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[24][2] = {
  {0, 0},
  {0, 1},
  {0, 2},
  {0, 3},
  {0, 4},
  {0, 5},
  {0, 6},
  {0, 7},
  {1, 0},
  {1, 1},
  {1, 2},
  {1, 3},
  {1, 4},
  {1, 5},
  {1, 6},
  {1, 7},
  {2, 0},
  {2, 1},
  {2, 2},
  {2, 3},
  {2, 4},
  {2, 5},
  {2, 6},
  {2, 7},
};

Radios radios;

void setup(void) {
  // No serial available for Prod,
  //  !!! Set DCSBIOS_IRQ_SERIAL in Arc210
  // Serial.begin(9600);

  radios.begin();

  Wire.begin(I2C_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Set the request event handler
}

void requestEvent()
{
  Wire.write(I2C_DATA, BUFFER_SIZE);
}

void loop(void) {
  radios.run();
}