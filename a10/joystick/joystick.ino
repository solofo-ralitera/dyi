#include <Joystick.h>
#include <Wire.h>

// Liste des modules
/////// LASTE and Throttle panel (24 buttons)
#define I2C_ADDRESS_LASTE 1 // Adresse I2C du module
#define BUFFER_SIZE_LASTE  3 // Taille en bytes (octets) des données envoyé par le module laste = taille de la plage de bit dans LAST_BUTTON_STATE
#define FIRST_BUTTON_NUMBER_LASTE 0 // numero du premier boutton du module
uint32_t  LastButtonStateLaste[1] = { 0 };// Store last state of the buttons of LASTE module (32bits) 

////// CDU
// TODO


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  128, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


// Compare le bit reçu vs le bit dans LAST_BUTTON_STATE[idx]
// Si même valeur -> raf
// Si différent -> set le statut du boutton en pressed (bitValue = 1) ou released (bitValue = 0) -> maj de la valeur du bit dans LAST_BUTTON_STATE
void checkBitStatus(byte bitValue, int firstButtonNumber, uint32_t *lastButtonsState, int bitPosition) {
  int numButton = firstButtonNumber + bitPosition;
  int lastButtonsStateIndex = 0;
  if (numButton > 63) {
    // Si le numéro du botton dépasse les 64 -> passe à l'index 2
    lastButtonsStateIndex = 2;
    bitPosition = bitPosition - 64;
  } else if (numButton > 31) {
    // Si le numéro du botton dépasse les 32 -> passe à l'index 1
    lastButtonsStateIndex = 1;
    bitPosition = bitPosition - 32;
  }

  // Si le bit est le même: raf pas d'action
  if (bitValue == bitRead(lastButtonsState[lastButtonsStateIndex], bitPosition)) {
    return;
  }
  if (bitValue) {
    Joystick.pressButton(numButton);
    bitSet(lastButtonsState[lastButtonsStateIndex], bitPosition);
  } else {
    Joystick.releaseButton(numButton);
    bitClear(lastButtonsState[lastButtonsStateIndex], bitPosition);
  }
}

// Lit le statut des boutons d'un module
// moduleI2CAdress -> adresse I2C du module
// moduleBufferSize -> taille des données I2C du module (en bytes)
// firstButtonNumber -> numéro du premier boutton du module
// lastButtonsState -> stockage de l'état des boutons du module
void readModule(int moduleI2CAdress, int moduleBufferSize, int firstButtonNumber, uint32_t *lastButtonsState) {
  // use to store each received bytes from i2c
  static byte wireBuffer = 0;

  Wire.requestFrom(moduleI2CAdress, moduleBufferSize);
  if(Wire.available() == moduleBufferSize) { // Si tous les données sont bien réccupérées
    // Loop sur chaque bytes reçcus
    for (int bytesIndex = 0; bytesIndex < moduleBufferSize; bytesIndex++) {
        wireBuffer = Wire.read();
        // Loop sur chaque bit du bytes pour avoir le statut de chaque boutton
        for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
          checkBitStatus(bitRead(wireBuffer, bitIndex), firstButtonNumber, lastButtonsState, bitIndex + (8 * bytesIndex));
        }
    }
  }
}

void setup() {
  // Serial.begin(9600);

  // Initialize Joystick Library
  Joystick.begin();
  Wire.begin(); // Activate I2C link
}

void loop() {
  #ifdef I2C_ADDRESS_LASTE
  readModule(I2C_ADDRESS_LASTE, BUFFER_SIZE_LASTE, FIRST_BUTTON_NUMBER_LASTE, LastButtonStateLaste);
  #endif
  
}

