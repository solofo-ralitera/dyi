#include "Arduino.h"

/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
#define DCSBIOS_IRQ_SERIAL
// #define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

#include "TftDisplay.h"

#include "Radios.h"
#include "modules/Arc210.h"
#include "modules/Uhf.h"
#include "modules/VhfFm.h"
#include "modules/Ils.h"
#include "modules/Tacan.h"

TftDisplay display;
Arc210 arc210(&display);
Uhf uhf(&display);
VhfFm vhfFm(&display);
Ils ils(&display);
Tacan tacan(&display);

// 0: arc210, VHF
// 1: UHF
// 2: VHF FM
// 3: ILS
// 4: TACAN
int currentRadio = 0;

void deactivateAllModules() {
  arc210.deactivate();
  uhf.deactivate();
  vhfFm.deactivate();
  ils.deactivate();
  tacan.deactivate();
  
  display.clearScreen();
}

void activateArc210() {
  if (arc210.isActive) return;
  deactivateAllModules();
  arc210.activate();
  display.printRadioTitle(0, arc210.title, uhf.title, vhfFm.title, ils.title, tacan.title);
}

void activateUhf() {
  if (uhf.isActive) return;
  deactivateAllModules();
  uhf.activate();
  display.printRadioTitle(1, arc210.title, uhf.title, vhfFm.title, ils.title, tacan.title);
}

void activateVhfFm() {
  if (vhfFm.isActive) return;
  deactivateAllModules();
  vhfFm.activate();
  display.printRadioTitle(2, arc210.title, uhf.title, vhfFm.title, ils.title, tacan.title);
}

void activateIls() {
  if (ils.isActive) return;
  deactivateAllModules();
  ils.activate();
  display.printRadioTitle(3, arc210.title, uhf.title, vhfFm.title, ils.title, tacan.title);
}

void activateTacan() {
  if (tacan.isActive) return;
  deactivateAllModules();
  tacan.activate();
  display.printRadioTitle(4, arc210.title, uhf.title, vhfFm.title, ils.title, tacan.title);
}

void activateNextModule() {
  if (arc210.isActive) {
    activateUhf();
  } else if (uhf.isActive) {
    activateVhfFm();
  } else if (vhfFm.isActive) {
    activateIls();
  } else if (ils.isActive) {
    activateTacan();
  } else if (tacan.isActive) {
    activateArc210();
  } else {
    activateArc210();
  }
}

void activatePreviousModule() {
  if (arc210.isActive) {
    activateTacan();
  } else if (uhf.isActive) {
    activateArc210();
  } else if (vhfFm.isActive) {
    activateUhf();
  } else if (ils.isActive) {
    activateVhfFm();
  } else if (tacan.isActive) {
    activateIls();
  } else {
    activateArc210();
  }
}

///////////// Arc-210 ////////////////////
DcsBios::StringBuffer<2> arc210ActiveChannelBuffer(A_10C_ARC210_ACTIVE_CHANNEL, [](char* newValue) {
  arc210.setChannel(newValue);
});
DcsBios::StringBuffer<7> arc210FrequencyBuffer(A_10C_ARC210_FREQUENCY, [](char* newValue) {
  arc210.setFrequency(newValue);
});
DcsBios::StringBuffer<2> arc210ModulationAmpFreqModulBuffer(A_10C_ARC210_MODULATION, [](char* newValue) {
  arc210.setModulation(newValue);
});
DcsBios::IntegerBuffer arc210MasterSwitchBuffer(A_10C_ARC210_MASTER, [](unsigned int newValue) {
  arc210.setSelectedMasterSwitch(newValue);
});
DcsBios::IntegerBuffer arc210SecSwitchBuffer(A_10C_ARC210_SEC_SW, [](unsigned int newValue) {
  arc210.setSelectedSecondarySwitch(newValue);
});
///////////// UHF ////////////////////
DcsBios::StringBuffer<2> uhfPresetBuffer(A_10C_UHF_PRESET, [](char* newValue) {
  uhf.setChannel(newValue);
});
DcsBios::StringBuffer<7> uhfFrequencyBuffer(A_10C_UHF_FREQUENCY, [](char* newValue) {
  uhf.setFrequency(newValue);
});
DcsBios::IntegerBuffer uhfMasterSwitchBuffer(A_10C_UHF_FUNCTION, [](unsigned int newValue) {
  uhf.setSelectedMasterSwitch(newValue);
});
DcsBios::IntegerBuffer uhfSecSwitchBuffer(A_10C_UHF_MODE, [](unsigned int newValue) {
  uhf.setSelectedSecondarySwitch(newValue);
});
///////////// VHF Fm ////////////////////
DcsBios::StringBuffer<2> vhfFmPresetBuffer(A_10C_VHFFM_PRESET, [](char* newValue) {
  vhfFm.setChannel(newValue);
});
DcsBios::StringBuffer<7> vhfFmFrequencyBuffer(A_10C_VHF_FM_FREQUENCY_S, [](char* newValue) {
  vhfFm.setFrequency(newValue);
});
DcsBios::IntegerBuffer vhfFmMasterSwitchBuffer(A_10C_VHFFM_FREQEMER, [](unsigned int newValue) {
  vhfFm.setSelectedMasterSwitch(newValue);
  activateVhfFm();
});
DcsBios::IntegerBuffer vhfFmSecSwitchBuffer(A_10C_VHFFM_MODE, [](unsigned int newValue) {
  vhfFm.setSelectedSecondarySwitch(newValue);
  activateVhfFm();
});
///////////// ILS ////////////////////
DcsBios::StringBuffer<6> ilsFrequencyBuffer(A_10C_ILS_FREQUENCY_S, [](char* newValue) {
  ils.setFrequency(newValue);
  activateIls();
});
DcsBios::IntegerBuffer ilsMasterSwitchBuffer(A_10C_ILS_PWR, [](unsigned int newValue) {
  ils.setSelectedMasterSwitch(newValue);
  activateIls();
});
///////////// TACAN ////////////////////
DcsBios::StringBuffer<4> tacanFrequencyBuffer(A_10C_TACAN_CHANNEL, [](char* newValue) {
  tacan.setFrequency(newValue);
  activateTacan();
});
DcsBios::IntegerBuffer tacanMasterSwitchBuffer(A_10C_TACAN_MODE, [](unsigned int newValue) {
  tacan.setSelectedMasterSwitch(newValue);
  activateTacan();
});

Radios::Radios()
{
}

void Radios::begin() {
  display.begin();
  DcsBios::setup();
  
 activateNextModule();
}

void Radios::run() {
  DcsBios::loop();

  // activateNextModule();
  // delay(2000);

}
