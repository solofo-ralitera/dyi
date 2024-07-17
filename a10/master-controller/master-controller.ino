#include <Joystick.h>
#include <Wire.h>
#include "MasterModule.h"

// Liste des modules
/////// LASTE and Throttle panel (24 buttons)
#define I2C_ADDRESS_LASTE 1 // Adresse I2C du module
#define BUFFER_SIZE_LASTE  3 // Taille en bytes (octets) des données envoyé par le module laste = taille de la plage de bit dans LAST_BUTTON_STATE
#define FIRST_BUTTON_NUMBER_LASTE 0 // numero du premier boutton du module
uint32_t LastButtonStateLaste[1] = { 0 };// Store last state of the buttons of LASTE module (32bits) 

/////// LASTE and Throttle panel (??? buttons)
#define I2C_ADDRESS_SAS 2 // Adresse I2C du module
#define BUFFER_SIZE_SAS  3 // Taille en bytes (octets) des données envoyé par le module laste = taille de la plage de bit dans LAST_BUTTON_STATE
#define FIRST_BUTTON_NUMBER_SAS 24 // numero du premier boutton du module
uint32_t LastButtonStateSas[1] = { 0 };// Store last state of the buttons of LASTE module (32bits) 

////// CDU
// TODO

MasterModule masterModule;

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
          Serial.println(bitRead(wireBuffer, bitIndex));
          masterModule.setBitAsJoystickStatus(bitRead(wireBuffer, bitIndex), firstButtonNumber, lastButtonsState, bitIndex + (8 * bytesIndex));
        }
    }
  }
}

void setup() {
  Serial.begin(9600);

  // Initialize Joystick Library
  Wire.begin(); // Activate I2C link
}

void loop() {
  #ifdef I2C_ADDRESS_LASTE
  readModule(I2C_ADDRESS_LASTE, BUFFER_SIZE_LASTE, FIRST_BUTTON_NUMBER_LASTE, LastButtonStateLaste);
  #endif

  #ifdef I2C_ADDRESS_SAS
  readModule(I2C_ADDRESS_SAS, BUFFER_SIZE_SAS, FIRST_BUTTON_NUMBER_SAS, LastButtonStateSas);
  #endif
  
}

