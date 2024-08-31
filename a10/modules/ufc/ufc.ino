/*******************************
Front UFC Panel (35 btns)
*******************************/

#include <Wire.h>
#include "PushButton.h"

// Adresse I2C du module
#define I2C_ADDRESS 6
// Taille des données I2C à tranmettre (en bytes)
#define BUFFER_SIZE 6
byte I2C_DATA[BUFFER_SIZE] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

#define UFC_0_KEY 0 // 
#define UFC_1_KEY 1 // 
#define UFC_2_KEY 2 // 
#define UFC_3_KEY 3 // 
#define UFC_4_KEY 4 // 
#define UFC_5_KEY 5 // 
#define UFC_6_KEY 6 // 
#define UFC_7_KEY 7 // 
#define UFC_8_KEY 8 // 
#define UFC_9_KEY 9 // 
#define UFC_ALT_KEY 10
#define UFC_CLEAR_KEY 11 //
#define UFC_COMM_1 12 // 
#define UFC_COMM_2 13 // 
#define UFC_DATA_DOWN 14
#define UFC_DATA_UP 15
#define UFC_DEPR_DOWN 16
#define UFC_DEPR_UP 17
#define UFC_ENT 18 // 
#define UFC_FUNC 19 // 
#define UFC_HACK 20 // 
#define UFC_INTEN_DECREASE 21
#define UFC_INTEN_INCREASE 22
#define UFC_LTR 23 // 
#define UFC_MASTER_CAUTION 24
#define UFC_MK 25 // 
#define UFC_SEL_DOWN 26
#define UFC_SEL_UP 27
#define UFC_SPC 28 // 
#define UFC_STEER_DOWN 29 //
#define UFC_STEER_UP 30 // 
#define UFC_ALT_ALTR 31 //!!!!!
#define UFC_COM_SEC 32 //!!!!!
#define UFC_ECCM 33 //!!!!!
#define UFC_IFF 34 //!!!!!
#define UFC_IDM 35 //!!!!!

#define NMSP_PTR 36
#define NMSP_HARS 37
#define NMSP_EGI 38
#define NMSP_TISL 39
#define NMSP_STRPT 40
#define NMSP_ANCHR 41
#define NMSP_TCN 42
#define NMSP_ILS 43


// Index de chaque boutton dans I2C_DATA (row, col)
byte BUTTON_INDEX[43][2] = {
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
  {3, 0},
  {3, 1},
  {3, 2},
  {3, 3},
  {3, 4},
  {3, 5},
  {3, 6},
  {3, 7},
  {4, 0},
  {4, 1},
  {4, 2},
  {4, 3},
  {4, 4},
  {4, 5},
  {4, 6},
  {4, 7},
  {5, 0},
  {5, 1},
  {5, 2},
};

#define ANALOG_SAMPLE 15

// Cf module radio.h
void getPBCode(int analogValue, int *numSample, int samples[], int *analogMean, int pullUpLow = 30, int pullUpHigh = 35) {
  // No press (32 à cause du pullup)
  if (analogValue >= pullUpLow && analogValue <= pullUpHigh){
    *numSample = 0; // Reset counter
    *analogMean = 0; // Reset mean
    return;
  } 

  if (*numSample < ANALOG_SAMPLE) {
    samples[*numSample] = analogValue;
    *numSample += 1;
    return;
  }
  if (*numSample == ANALOG_SAMPLE) {
    // Calc moyenne
    long sum = 0L;
    for (int i = 0; i < ANALOG_SAMPLE; i++) {
      sum += samples[i];
    }
    *analogMean = sum / ANALOG_SAMPLE;
  }
}

void setup() {
  // Serial.begin(9600);

  // UFC
  pinMode(A2, INPUT_PULLUP); // Right buttons
  pinMode(A3, INPUT_PULLUP); // Left buttons
  pinMode(A6, INPUT); // NMSP

  // NMSP
  pinMode(4, INPUT_PULLUP);

  Wire.begin(I2C_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Set the request event handler

}

void requestEvent()
{
  Wire.write(I2C_DATA, BUFFER_SIZE);
}

void loop() {

  static int numSampleUfcRight = 0;
  static int samplesUfcRight[ANALOG_SAMPLE];
  static int analogMeanUfcRight = 0;
  getPBCode(analogRead(A2), &numSampleUfcRight, samplesUfcRight, &analogMeanUfcRight);

  static int numSampleUfcLeft = 0;
  static int samplesUfcLeft[ANALOG_SAMPLE];
  static int analogMeanUfcLeft = 0;
  getPBCode(analogRead(A3), &numSampleUfcLeft, samplesUfcLeft, &analogMeanUfcLeft);

  static int numSampleNmsp = 0;
  static int samplesNmsp[ANALOG_SAMPLE];
  static int analogMeanNmsp = 0;
  getPBCode(analogRead(A6), &numSampleNmsp, samplesNmsp, &analogMeanNmsp, 146, 150);

  // NMSP
  static PushButton ptr(I2C_DATA, BUTTON_INDEX[NMSP_PTR]);  
  ptr.run(bitRead(PIND, PIND4));

  static PushButton hars(I2C_DATA, BUTTON_INDEX[NMSP_HARS]);  
  hars.run((analogMeanNmsp >= 193 && analogMeanNmsp <= 197) ? 0 : 1);

  static PushButton egi(I2C_DATA, BUTTON_INDEX[NMSP_EGI]);  
  egi.run((analogMeanNmsp >= 386 && analogMeanNmsp <= 390) ? 0 : 1);

  static PushButton tisl(I2C_DATA, BUTTON_INDEX[NMSP_TISL]);  
  tisl.run((analogMeanNmsp >= 528 && analogMeanNmsp <= 532) ? 0 : 1);

  static PushButton strPt(I2C_DATA, BUTTON_INDEX[NMSP_STRPT]);  
  strPt.run((analogMeanNmsp >= 208 && analogMeanNmsp <= 212) ? 0 : 1);

  static PushButton anchr(I2C_DATA, BUTTON_INDEX[NMSP_ANCHR]);  
  anchr.run((analogMeanNmsp >= 248 && analogMeanNmsp <= 252) ? 0 : 1);

  static PushButton tcn(I2C_DATA, BUTTON_INDEX[NMSP_TCN]);  
  tcn.run((analogMeanNmsp >= 275 && analogMeanNmsp <= 280) ? 0 : 1);

  static PushButton ils(I2C_DATA, BUTTON_INDEX[NMSP_ILS]);  
  ils.run((analogMeanNmsp >= 317 && analogMeanNmsp <= 321) ? 0 : 1);


  //////// Ufc right part
  static PushButton deprUp(I2C_DATA, BUTTON_INDEX[UFC_DEPR_UP]);  
  deprUp.run((analogMeanUfcRight >= 504 && analogMeanUfcRight <= 508) ? 0 : 1);

  static PushButton deprDown(I2C_DATA, BUTTON_INDEX[UFC_DEPR_DOWN]);  
  deprDown.run((analogMeanUfcRight >= 340 && analogMeanUfcRight <= 344) ? 0 : 1);

  static PushButton selUp(I2C_DATA, BUTTON_INDEX[UFC_SEL_UP]);  
  selUp.run((analogMeanUfcRight >= 156 && analogMeanUfcRight <= 160) ? 0 : 1);

  static PushButton selDown(I2C_DATA, BUTTON_INDEX[UFC_SEL_DOWN]);  
  selDown.run((analogMeanUfcRight >= 179 && analogMeanUfcRight <= 183) ? 0 : 1);

  static PushButton dataUp(I2C_DATA, BUTTON_INDEX[UFC_DATA_UP]);  
  dataUp.run((analogMeanUfcRight >= 124 && analogMeanUfcRight <= 128) ? 0 : 1);

  static PushButton dataDown(I2C_DATA, BUTTON_INDEX[UFC_DATA_DOWN]);  
  dataDown.run((analogMeanUfcRight >= 138 && analogMeanUfcRight <= 142) ? 0 : 1);

  static PushButton intenIncrease(I2C_DATA, BUTTON_INDEX[UFC_INTEN_INCREASE]);  
  intenIncrease.run((analogMeanUfcRight >= 259 && analogMeanUfcRight <= 263) ? 0 : 1);

  static PushButton intenDecrease(I2C_DATA, BUTTON_INDEX[UFC_INTEN_DECREASE]);  
  intenDecrease.run((analogMeanUfcRight >= 211 && analogMeanUfcRight <= 215) ? 0 : 1);

  static PushButton ufcIff(I2C_DATA, BUTTON_INDEX[UFC_IFF]);  
  ufcIff.run((analogMeanUfcRight >= 102 && analogMeanUfcRight <= 106) ? 0 : 1);

  static PushButton ufcIdm(I2C_DATA, BUTTON_INDEX[UFC_IDM]);  
  ufcIdm.run((analogMeanUfcRight >= 93 && analogMeanUfcRight <= 97) ? 0 : 1);

  static PushButton comSec(I2C_DATA, BUTTON_INDEX[UFC_COM_SEC]);  
  comSec.run((analogMeanUfcRight >= 72 && analogMeanUfcRight <= 76) ? 0 : 1);

  static PushButton eccm(I2C_DATA, BUTTON_INDEX[UFC_ECCM]);  
  eccm.run((analogMeanUfcRight >= 83 && analogMeanUfcRight <= 87) ? 0 : 1);

  static PushButton comm1(I2C_DATA, BUTTON_INDEX[UFC_COMM_1]);  
  comm1.run((analogMeanUfcRight >= 55 && analogMeanUfcRight <= 59) ? 0 : 1);

  static PushButton comm2(I2C_DATA, BUTTON_INDEX[UFC_COMM_2]);  
  comm2.run((analogMeanUfcRight >= 13 && analogMeanUfcRight <= 17) ? 0 : 1);

  static PushButton masterCaution(I2C_DATA, BUTTON_INDEX[UFC_MASTER_CAUTION]);  
  masterCaution.run((analogMeanUfcRight >= 112 && analogMeanUfcRight <= 116) ? 0 : 1);


  //////// Ufc left part
  static PushButton steerUp(I2C_DATA, BUTTON_INDEX[UFC_STEER_UP]);  
  steerUp.run((analogMeanUfcLeft >= 345 && analogMeanUfcLeft <= 349) ? 0 : 1);

  static PushButton steerDown(I2C_DATA, BUTTON_INDEX[UFC_STEER_DOWN]);  
  steerDown.run((analogMeanUfcLeft >= 509 && analogMeanUfcLeft <= 513) ? 0 : 1);

  static PushButton ufc1(I2C_DATA, BUTTON_INDEX[UFC_1_KEY]);  
  ufc1.run((analogMeanUfcLeft >= 264 && analogMeanUfcLeft <= 268) ? 0 : 1);

  static PushButton ufc2(I2C_DATA, BUTTON_INDEX[UFC_2_KEY]);  
  ufc2.run((analogMeanUfcLeft >= 130 && analogMeanUfcLeft <= 134) ? 0 : 1);

  static PushButton ufc3(I2C_DATA, BUTTON_INDEX[UFC_3_KEY]);  
  ufc3.run((analogMeanUfcLeft >= 119 && analogMeanUfcLeft <= 123) ? 0 : 1);

  static PushButton ufc4(I2C_DATA, BUTTON_INDEX[UFC_4_KEY]);  
  ufc4.run((analogMeanUfcLeft >= 216 && analogMeanUfcLeft <= 220) ? 0 : 1);

  static PushButton ufc5(I2C_DATA, BUTTON_INDEX[UFC_5_KEY]);
  ufc5.run((analogMeanUfcLeft >= 143 && analogMeanUfcLeft <= 147) ? 0 : 1);

  static PushButton ufc6(I2C_DATA, BUTTON_INDEX[UFC_6_KEY]);
  ufc6.run((analogMeanUfcLeft >= 110 && analogMeanUfcLeft <= 114) ? 0 : 1);

  static PushButton ufc7(I2C_DATA, BUTTON_INDEX[UFC_7_KEY]);
  ufc7.run((analogMeanUfcLeft >= 184 && analogMeanUfcLeft <= 188) ? 0 : 1);

  static PushButton ufc8(I2C_DATA, BUTTON_INDEX[UFC_8_KEY]);
  ufc8.run((analogMeanUfcLeft >= 161 && analogMeanUfcLeft <= 165) ? 0 : 1);

  static PushButton ufc9(I2C_DATA, BUTTON_INDEX[UFC_9_KEY]);
  ufc9.run((analogMeanUfcLeft >= 102 && analogMeanUfcLeft <= 106) ? 0 : 1);

  static PushButton ufc0(I2C_DATA, BUTTON_INDEX[UFC_0_KEY]);
  ufc0.run((analogMeanUfcLeft >= 90 && analogMeanUfcLeft <= 93) ? 0 : 1);

  static PushButton hack(I2C_DATA, BUTTON_INDEX[UFC_HACK]);
  hack.run((analogMeanUfcLeft >= 85 && analogMeanUfcLeft <= 88) ? 0 : 1);

  static PushButton spc(I2C_DATA, BUTTON_INDEX[UFC_SPC]);
  spc.run((analogMeanUfcLeft >= 95 && analogMeanUfcLeft <= 99) ? 0 : 1);

  static PushButton func(I2C_DATA, BUTTON_INDEX[UFC_FUNC]);
  func.run((analogMeanUfcLeft >= 79 && analogMeanUfcLeft <= 82) ? 0 : 1);

  static PushButton ltr(I2C_DATA, BUTTON_INDEX[UFC_LTR]);
  ltr.run((analogMeanUfcLeft >= 74 && analogMeanUfcLeft <= 76) ? 0 : 1);

  static PushButton clr(I2C_DATA, BUTTON_INDEX[UFC_CLEAR_KEY]);
  clr.run((analogMeanUfcLeft >= 68 && analogMeanUfcLeft <= 70) ? 0 : 1);

  static PushButton altAltr(I2C_DATA, BUTTON_INDEX[UFC_ALT_ALTR]);
  altAltr.run((analogMeanUfcLeft >= 59 && analogMeanUfcLeft <= 63) ? 0 : 1);

  static PushButton mk(I2C_DATA, BUTTON_INDEX[UFC_MK]);
  mk.run((analogMeanUfcLeft >= 46 && analogMeanUfcLeft <= 50) ? 0 : 1);

  static PushButton ent(I2C_DATA, BUTTON_INDEX[UFC_ENT]);
  ent.run((analogMeanUfcLeft >= 12 && analogMeanUfcLeft <= 16) ? 0 : 1);

}
