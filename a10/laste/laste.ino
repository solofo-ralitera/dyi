// Module LASTE
// EAC switch, 2 positions
// Radar Altimeter switch, 2 positions
// Auto pilot Engage/Disengage, push button
// Auto pilot select switch, 3 positions
//------------------------------------------------------------

#include <Wire.h>

// Adresse I2C du module
#define I2C_ADDRESS 1

// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 2

#define DEBOUNCE_DELAY 100 // millis

byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000
};

void setup() {
  Serial.begin(9600);

  /**
  // DDRX => Registre de config des ports entrée/sortie
  //          X: B/C/D, ex: DDRB
  //    DDXN => index de chaque bit (= pin, cf pinout) du registre
  //        0 = entrée, 1 = sortie
  //        ex: DDB0 correspond au pin 8 (PB0) du nano
  **/
  // Force les digitals pins des ports B/C/D en configuration entrée (0), 
  // !!! pin 0 et 1 non disponible quand Serial est activé
  // !!! pin A4 et A5 pour l'I2C
  DDRB = DDRB & ~((1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5));
  DDRC = DDRC & ~((1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3));
  DDRD = DDRD & ~((1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) | (1<<DDD7));

  /**
  //  Pour un pin configuré en entrée: pour activer la resistance de pullup: set PORTXN à 1
  **/
  // Force tous les inputs pins en pullup (1)
  PORTB |= ((1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5));
  PORTC |= ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3));
  PORTD |= ((1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD5) | (1<<PORTD6) | (1<<PORTD7));

  //      
  //
  // PINX => Registre pour lire l'état des pin d'entrée (input)
  //          X: B/C/D
  //    PINXN => pour lire l'état d'entrée, 0 LOW, 1 HIGH
  //
  //
  // PORTX => Registre pour lire l'état des pin d'entrée (input)
  //          X: B/C/D
  //    PORTXN => pour ecrire l'état de sortie
  //

  
  // put your setup code here, to run once:
  Wire.begin(I2C_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Set the request event handler
}

void requestEvent()
{
  Wire.write(I2C_DATA, BUFFER_SIZE);
}

void loop() {
  
  // Cas boutton poussoir
  if (bitRead(PIND, PIND2) == 0) {
    bitSet(I2C_DATA[0], 1);
  } else {
    bitClear(I2C_DATA[0], 1);
  }
  

  // Cas bouton 2 positions
  //  OFF -> ON: active un boutton, sans garder le statut maintenir
  //  ON -> OFF: active un autre boutton

}
