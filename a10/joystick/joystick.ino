#include <Joystick.h>
#include <Wire.h>

// Liste des modules
/////// LASTE
#define I2C_ADDRESS_LASTE 1 // Adresse I2C du module
#define INDEX_IN_STATE_LASTE 1 // Position de départ de la plage de bit dans LAST_BUTTON_STATE
#define BUFFER_SIZE_LASTE  3 // Taille en bytes (octets) des données envoyé par le module laste = taille de la plage de bit dans LAST_BUTTON_STATE

////// CDU
// TODO


// Store last state of all buttons (128bits) 
// Each row represent the last state of the butons of an module
// Each bit of stored data represent the state of one button
unsigned long LAST_BUTTON_STATE[4] = {
  0, // Laste panel and Throttle panel
  0,
  0,
  0,
};


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  128, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


// Compare le bit reçu vs le bit dans LAST_BUTTON_STATE[idx]
// Si même valeur -> raf
// Si différent -> set le statut du boutton en pressed (bitValue = 1) ou released (bitValue = 0) -> maj de la valeur du bit dans LAST_BUTTON_STATE
void checkBitStatus(byte bitValue, int indexInLastState, int bitPosition) {
  // Si le bit est le même: raf pas d'action
  if (bitValue == bitRead(LAST_BUTTON_STATE[indexInLastState], bitPosition)) {
    return;
  }
  int numButton = (indexInLastState * 32) + bitPosition;
  if (bitValue) {
    Joystick.pressButton(numButton);
    bitSet(LAST_BUTTON_STATE[indexInLastState], bitPosition);
  } else {
    Joystick.releaseButton(numButton);
    bitClear(LAST_BUTTON_STATE[indexInLastState], bitPosition);
  }
}

// Lit le statut des boutons d'un module
// moduleI2CAdress -> adress I2C du module
// indexInLastState -> index du module dans LAST_BUTTON_STATE
// moduleBufferSize -> taille des données du module à transférervia I2C
void readModule(int moduleI2CAdress, int indexInLastState, int moduleBufferSize) {
  // use to store each received bytes from i2c
  static byte wireBuffer = 0;

  Wire.requestFrom(moduleI2CAdress, moduleBufferSize);
  if(Wire.available() == moduleBufferSize) { // Si tous les données sont bien réccupérées
    // Loop sur chaque bytes reçcus
    for (int bytesIndex = 0; bytesIndex < moduleBufferSize; bytesIndex++) {
        wireBuffer = Wire.read();
        // Loop sur chaque bit du bytes pour avoir le statut de chaque boutton
        for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
          checkBitStatus(bitRead(wireBuffer, bitIndex), indexInLastState, bitIndex + (8 * bytesIndex));
        }
    }
  }
}

void setup() {
  // Initialize Joystick Library
  Joystick.begin();
  Wire.begin(); // Activate I2C link
}

void loop() {
  #ifdef I2C_ADDRESS_LASTE
  readModule(I2C_ADDRESS_LASTE, INDEX_IN_STATE_LASTE, BUFFER_SIZE_LASTE);
  #endif
  
}

