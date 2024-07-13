#include <Joystick.h>
#include <Wire.h>

// Liste des modules
/////// LASTE
#define I2C_ADDRESS_LASTE 1 // Adresse I2C du module
#define BUFFER_OFFSET_START_LASTE 0 // Position de départ de la plage de bit dans LAST_BUTTON_STATE
#define BUFFER_SIZE_LASTE  2 // Taille en bytes des données envoyé par le module laste = taille de la plage de bit dans LAST_BUTTON_STATE

////// CDU
// TODO

/// Conf debug
// #define DEBUG_BIT_STATUS 1
// #define DEBUG_LAST_BUTTON_STATE 1

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  128, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

// Store last state of all buttons, each bit represent the status of one button
// TODO: store up to 128bits
unsigned long LAST_BUTTON_STATE = 0;

// use to store each received bytes from i2c
byte wireBuffer = 0;

// Compare le bit reçu vs le bit dans LAST_BUTTON_STATE
// Si même valeur -> raf
// Si différent -> set le statut du boutton en pressed (bitValue = 1) ou released (bitValue = 0) -> maj de la valeur du bit dans LAST_BUTTON_STATE
void checkBitStatus(byte bitValue, int offsetStart, int bitPosition) {
  int numButton = offsetStart + bitPosition;
  if (bitValue == bitRead(LAST_BUTTON_STATE, numButton)) {
    return;
  }
  #ifdef DEBUG_BIT_STATUS
    Serial.print(numButton);
    Serial.print("---");
  #endif
  if (bitValue) {
    #ifdef DEBUG_BIT_STATUS
      Serial.print("Pressed");
    #endif
    Joystick.pressButton(numButton);
    bitSet(LAST_BUTTON_STATE, numButton);
  } else {
    #ifdef DEBUG_BIT_STATUS
      Serial.print("Realeased");
    #endif
    Joystick.releaseButton(numButton);
    bitClear(LAST_BUTTON_STATE, numButton);
  }
  #ifdef DEBUG_BIT_STATUS
    Serial.println("");
  #endif
}

// Lit le statut des boutons d'un module
// moduleI2CAdress -> adress I2C du module
// moduleOffsetStart -> index de début de la plage du module dans LAST_BUTTON_STATE
// moduleBufferSize -> taille des données du module (= taille du data I2C, = taille de la plage dans LAST_BUTTON_STATE)
void readModule(int moduleI2CAdress, int moduleOffsetStart, int moduleBufferSize) {
  Wire.requestFrom(moduleI2CAdress, moduleBufferSize);
  if(Wire.available() == moduleBufferSize) { // Si tous les données sont bien réccupérées
    // Loop sur chaque bytes reçcus
    for (int bytesIndex = 0; bytesIndex < moduleBufferSize; bytesIndex++) {
        wireBuffer = Wire.read();
        // Loop sur chaque bit du bytes pour avoir le statut de chaque boutton
        for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
          checkBitStatus(bitRead(wireBuffer, bitIndex), moduleOffsetStart, bitIndex + (8 * bytesIndex));
        }
    }
  }
}

void setup() {
  Serial.begin(9600);

  // Initialize Joystick Library
  Joystick.begin();
  Wire.begin(); // Activate I2C link
}

void loop() {
  #ifdef I2C_ADDRESS_LASTE
  readModule(I2C_ADDRESS_LASTE, BUFFER_OFFSET_START_LASTE, BUFFER_SIZE_LASTE);
  #endif
  
  #ifdef DEBUG_LAST_BUTTON_STATE
  for (int j = 15; j >= 0; j--) {
    Serial.print(bitRead(LAST_BUTTON_STATE, j));
  }
  Serial.println("");
  #endif
}

