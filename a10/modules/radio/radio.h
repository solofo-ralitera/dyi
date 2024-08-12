/*
Gestion des radios Arc10, Com, UHF, ILS, Tacan
*/
#ifndef radio_h
#define radio_h

#define PB_TOP_SCREEN 1000
#define PB_MIDDLE_SCREEN 500
#define PB_BOTTOM_SCREEN 340
#define PB_FREQUENCY_SELECTOR_1 260
#define PB_FREQUENCY_SELECTOR_2 212
#define PB_MASTER_MODE 178
#define PB_CHANNEL 155
#define PB_FREQUENCY_SELECTOR_3 140
#define PB_FREQUENCY_SELECTOR_4 127
#define PB_FREQUENCY_SELECTOR_5 115
#define PB_SECONDARY_MODE 105
#define PB_MOD_SELECTOR 97
#define PB_OFFSET 90
#define PB_AMFM 83
#define PB_VOLUME 73
#define PB_SQL 64
#define PB_MENU 48
#define PB_XMTRCV 12

#define ANALOG_SAMPLE 15
int numSample = 0;
int samples[ANALOG_SAMPLE];
int analogMean = 0;

int getPBCode(int analogValue) {
  // No press (32 à cause du pullup)
  if (analogValue > 30 && analogValue < 37){
    numSample = 0; // Reset counter
    analogMean = 0; // Reset mean
    return 0;
  } 
  // Serial.println(analogValue);

  // Calcul la moyenne de l'analog sur 15 valeurs
  // Reccup une echantillon de 15 valeurs
  if (numSample < ANALOG_SAMPLE) {
    samples[numSample] = analogValue;
    numSample++;
  } else if (numSample == ANALOG_SAMPLE) {
    // Calc moyenne
    long sum = 0L;
    for (int i = 0; i < ANALOG_SAMPLE; i++) {
      sum += samples[i];
      samples[i] = 0; // Reset each value
    }
    analogMean = sum / ANALOG_SAMPLE;
  }

  if (analogMean > PB_TOP_SCREEN) return PB_TOP_SCREEN;
  if (analogMean > PB_MIDDLE_SCREEN) return PB_MIDDLE_SCREEN;
  if (analogMean > PB_BOTTOM_SCREEN) return PB_BOTTOM_SCREEN;
  if (analogMean > PB_FREQUENCY_SELECTOR_1) return PB_FREQUENCY_SELECTOR_1;
  if (analogMean > PB_FREQUENCY_SELECTOR_2) return PB_FREQUENCY_SELECTOR_2;
  if (analogMean > PB_MASTER_MODE) return PB_MASTER_MODE;
  if (analogMean > PB_CHANNEL) return PB_CHANNEL;
  if (analogMean > PB_FREQUENCY_SELECTOR_3) return PB_FREQUENCY_SELECTOR_3;
  if (analogMean > PB_FREQUENCY_SELECTOR_4) return PB_FREQUENCY_SELECTOR_4;
  if (analogMean > PB_FREQUENCY_SELECTOR_5) return PB_FREQUENCY_SELECTOR_5;
  if (analogMean > PB_SECONDARY_MODE) return PB_SECONDARY_MODE;
  if (analogMean > PB_MOD_SELECTOR) return PB_MOD_SELECTOR;
  if (analogMean > PB_OFFSET) return PB_OFFSET;
  if (analogMean > PB_AMFM) return PB_AMFM;
  if (analogMean > PB_VOLUME) return PB_VOLUME;
  if (analogMean > PB_SQL) return PB_SQL;
  if (analogMean > PB_MENU) return PB_MENU;
  if (analogMean > PB_XMTRCV) return PB_XMTRCV;
}

#endif

