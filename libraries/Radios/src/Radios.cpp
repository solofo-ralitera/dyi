#include "Arduino.h"

/*c
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
#include "modules/intercomPanel.h"
#include "modules/CheckLists.h"

#include "modules/ledMatrix.h"
#include "modules/servoIndicators.h"

TftDisplay display;
Arc210 arc210(&display);
Uhf uhf(&display);
VhfFm vhfFm(&display);
Ils ils(&display);
Tacan tacan(&display);
IntercomPanel intercomPanel(&display);
CheckLists checklists(&display);

// 0: arc210, VHF
// 1: UHF
// 2: VHF FM
// 3: ILS
// 4: TACAN
// 5: Intercom
// 6: Checklists
int currentRadio = -1;

void deactivateAllModules() {
  arc210.deactivate();
  uhf.deactivate();
  vhfFm.deactivate();
  ils.deactivate();
  tacan.deactivate();
  intercomPanel.deactivate();
  checklists.deactivate();

  display.clearScreen();
}

void activateArc210() {
  if (arc210.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(arc210.title);
  arc210.activate();
  currentRadio = 0;
}

void activateUhf() {
  if (uhf.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(uhf.title);
  uhf.activate();
  currentRadio = 1;
}

void activateVhfFm() {
  if (vhfFm.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(vhfFm.title);
  vhfFm.activate();
  currentRadio = 2;
}

void activateIls() {
  if (ils.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(ils.title);
  ils.activate();
  currentRadio = 3;
}

void activateTacan() {
  if (tacan.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(tacan.title);
  tacan.activate();
  currentRadio = 4;
}

void activateIntercomPanel() {
  if (intercomPanel.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(intercomPanel.title);
  intercomPanel.activate();
  currentRadio = 5;
}

void activateCheckLists() {
  if (checklists.isActive) return;
  deactivateAllModules();
  display.printRadioTitle(checklists.title);
  checklists.activate();
  currentRadio = 6;
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
DcsBios::IntegerBuffer arc210SqlBuffer(A_10C_ARC210_SQUELCH, [](unsigned int newValue) {
  arc210.setSql(newValue);
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
DcsBios::IntegerBuffer uhfVolumeBuffer(A_10C_UHF_VOL, [](unsigned int newValue) {
  uhf.setVolume(map(newValue, 0, 65535, 0, 100));
});
DcsBios::IntegerBuffer uhfSqlBuffer(A_10C_UHF_SQUELCH, [](unsigned int newValue) {
  uhf.setSql(newValue);
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
});
DcsBios::IntegerBuffer vhfFmSecSwitchBuffer(A_10C_VHFFM_MODE, [](unsigned int newValue) {
  vhfFm.setSelectedSecondarySwitch(newValue);
});
DcsBios::IntegerBuffer vhfFmVolumeBuffer(A_10C_VHFFM_VOL, [](unsigned int newValue) {
  vhfFm.setVolume(map(newValue, 0, 65535, 0, 100));
});
DcsBios::IntegerBuffer vhfFmSqlBuffer(A_10C_VHFFM_SQUELCH, [](unsigned int newValue) {
  vhfFm.setSql(newValue);
});
///////////// ILS ////////////////////
DcsBios::StringBuffer<6> ilsFrequencyBuffer(A_10C_ILS_FREQUENCY_S, [](char* newValue) {
  ils.setFrequency(newValue);
});
DcsBios::IntegerBuffer ilsMasterSwitchBuffer(A_10C_ILS_PWR, [](unsigned int newValue) {
  ils.setSelectedMasterSwitch(newValue);
});
DcsBios::IntegerBuffer ilsVolumeBuffer(A_10C_ILS_VOL, [](unsigned int newValue) {
  ils.setVolume(map(newValue, 0, 65535, 0, 100));
});
DcsBios::IntegerBuffer ilsToneBuffer(A_10C_INT_ILS_UNMUTE, [](unsigned int newValue) {
  ils.setTone(newValue);
});
///////////// TACAN ////////////////////
DcsBios::StringBuffer<4> tacanFrequencyBuffer(A_10C_TACAN_CHANNEL, [](char* newValue) {
  tacan.setFrequency(newValue);
});
DcsBios::IntegerBuffer tacanMasterSwitchBuffer(A_10C_TACAN_MODE, [](unsigned int newValue) {
  tacan.setSelectedMasterSwitch(newValue);
});
DcsBios::IntegerBuffer tacanVolumeBuffer(A_10C_TACAN_VOL, [](unsigned int newValue) {
  tacan.setVolume(map(newValue, 0, 65535, 0, 100));
});
DcsBios::IntegerBuffer tacanTestBuffer(A_10C_TACAN_TEST, [](unsigned int newValue) {
  tacan.setTest(newValue);
});
DcsBios::IntegerBuffer tacanToneBuffer(A_10C_INT_TCN_UNMUTE, [](unsigned int newValue) {
  tacan.setTone(newValue);
});
///////////// INTERCOM ////////////////////
DcsBios::IntegerBuffer intercomSecSwitchBuffer(A_10C_INT_MODE, [](unsigned int newValue) {
  intercomPanel.setSelectedSecondarySwitch(newValue);
});
DcsBios::IntegerBuffer intercomVolumeBuffer(A_10C_INT_VOL, [](unsigned int newValue) {
  intercomPanel.setVolume(map(newValue, 0, 65535, 0, 100));
});
DcsBios::IntegerBuffer intercomHMBuffer(A_10C_INT_HM, [](unsigned int newValue) {
  intercomPanel.setHm(newValue);
});
// Int
DcsBios::IntegerBuffer intercomIntUnmuteBuffer(A_10C_INT_INT_UNMUTE, [](unsigned int newValue) {
  intercomPanel.setIntUnmute(newValue);
});
DcsBios::IntegerBuffer intercomIntVolumeBuffer(A_10C_INT_INT_VOL, [](unsigned int newValue) {
  intercomPanel.setIntVolume(map(newValue, 0, 65535, 0, 100));
});
// Aim
DcsBios::IntegerBuffer intercomAimUnmuteBuffer(A_10C_INT_AIM_UNMUTE, [](unsigned int newValue) {
  intercomPanel.setAimUnmute(newValue);
});
DcsBios::IntegerBuffer intercomAimVolumeBuffer(A_10C_INT_AIM_VOL, [](unsigned int newValue) {
  intercomPanel.setAimVolume(map(newValue, 0, 65535, 0, 100));
});
// Fm
DcsBios::IntegerBuffer intercomFmUnmuteBuffer(A_10C_INT_FM_UNMUTE, [](unsigned int newValue) {
  intercomPanel.setFmUnmute(newValue);
});
DcsBios::IntegerBuffer intercomFmVolumeBuffer(A_10C_INT_FM_VOL, [](unsigned int newValue) {
  intercomPanel.setFmVolume(map(newValue, 0, 65535, 0, 100));
});
// Uhf
DcsBios::IntegerBuffer intercomUhfUnmuteBuffer(A_10C_INT_UHF_UNMUTE, [](unsigned int newValue) {
  intercomPanel.setUhfUnmute(newValue);
});
DcsBios::IntegerBuffer intercomUhfVolumeBuffer(A_10C_INT_UHF_VOL, [](unsigned int newValue) {
  intercomPanel.setUhfVolume(map(newValue, 0, 65535, 0, 100));
});
// Vhf
DcsBios::IntegerBuffer intercomVhfUnmuteBuffer(A_10C_INT_VHF_UNMUTE, [](unsigned int newValue) {
  intercomPanel.setVhfUnmute(newValue);
});
DcsBios::IntegerBuffer intercomVhfVolumeBuffer(A_10C_INT_VHF_VOL, [](unsigned int newValue) {
  intercomPanel.setVhfVolume(map(newValue, 0, 65535, 0, 100));
  // Arc 210 has no volume knob, use VHF volume
  arc210.setVolume(map(newValue, 0, 65535, 0, 100));
});

/*****************************************************
*********** Led Display ******************************
*****************************************************/
// Landing gear
DcsBios::IntegerBuffer landingGearLSafeBuffer(A_10C_GEAR_L_SAFE, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_LANDING_GEAR_L_SAFE, newValue);
});
DcsBios::IntegerBuffer landingGearNSafeBuffer(A_10C_GEAR_N_SAFE, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_LANDING_GEAR_N_SAFE, newValue);
});
DcsBios::IntegerBuffer landingGearRSafeBuffer(A_10C_GEAR_R_SAFE, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_LANDING_GEAR_R_SAFE, newValue);
});
DcsBios::IntegerBuffer antiskidBuffer(A_10C_ANTI_SKID_SWITCH, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_ANTISKID, newValue);
});
DcsBios::IntegerBuffer handleGearWarningBuffer(A_10C_HANDLE_GEAR_WARNING, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_HANDLE_GEAR_WARNING, newValue);
});
DcsBios::IntegerBuffer flapsPosBuffer(A_10C_FLAP_POS, [](unsigned int newValue) {
    servoIndicatosSetFlaps(newValue);
});
// SAS
DcsBios::IntegerBuffer yawSasLBuffer(A_10C_SASP_YAW_SAS_L, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_YAW_SAS_ENGAGE_L, newValue);
});
DcsBios::IntegerBuffer yawSasRBuffer(A_10C_SASP_YAW_SAS_R, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_YAW_SAS_ENGAGE_R, newValue);
});
DcsBios::IntegerBuffer pitchSasLBuffer(A_10C_SASP_PITCH_SAS_L, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_PITCH_SAS_ENGAGE_L, newValue);
});
DcsBios::IntegerBuffer pitchSasRBuffer(A_10C_SASP_PITCH_SAS_R, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_PITCH_SAS_ENGAGE_R, newValue);
});
// LASTE
DcsBios::IntegerBuffer eacBuffer(A_10C_LASTE_EAC, [](unsigned int newValue) {
  // For eac, lit only if disabled
  ledMatrixSet(LED_MATRIX_EAC, newValue == 1 ? false : true);
});
//UFC
DcsBios::IntegerBuffer masterCautionBuffer(A_10C_MASTER_CAUTION, [](unsigned int newValue) {
  // For eac, lit only if disabled
  ledMatrixSet(LED_MATRIX_MASTER_CAUTION, newValue);
});
// External lights
DcsBios::IntegerBuffer extStrobeLeftBuffer(A_10C_EXT_STROBE_LEFT, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_EXT_STROBE_LEFT, newValue);
});
DcsBios::IntegerBuffer extStrobeRightBuffer(A_10C_EXT_STROBE_RIGHT, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_EXT_STROBE_RIGHT, newValue);
});
DcsBios::IntegerBuffer extPositionRightBuffer(A_10C_EXT_POSITION_LIGHT_RIGHT, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_EXT_POSITION_RIGHT, newValue);
});
DcsBios::IntegerBuffer extPositionLeftBuffer(A_10C_EXT_POSITION_LIGHT_LEFT, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_EXT_POSITION_LEFT, newValue);
});
// NMPSP
DcsBios::IntegerBuffer tislBuffer(A_10C_NMSP_TISL_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_TISL, newValue);
});
DcsBios::IntegerBuffer ilsBuffer(A_10C_NMSP_ILS_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_ILS, newValue);
});
DcsBios::IntegerBuffer egiBuffer(A_10C_NMSP_EGI_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_EGI, newValue);
});
DcsBios::IntegerBuffer tcnBuffer(A_10C_NMSP_TCN_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_TCN, newValue);
});
DcsBios::IntegerBuffer anchrBuffer(A_10C_NMSP_ANCHR_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_ANCHR, newValue);
});
DcsBios::IntegerBuffer strptBuffer(A_10C_NMSP_STEERPT_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_STRPT, newValue);
});
DcsBios::IntegerBuffer harsBuffer(A_10C_NMSP_HARS_LED, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_HARS, newValue);
});
// Emer brake
DcsBios::IntegerBuffer emerbrakeBuffer(A_10C_EMER_BRAKE, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_EMERBRAKE, newValue);
});
// APU
DcsBios::IntegerBuffer apuBuffer(A_10C_APU_RPM, [](unsigned int newValue) {
  ledMatrixSet(LED_MATRIX_APU, map(newValue, 0, 65535, 0, 100) > 80 ? 1 : 0);
});

Radios::Radios()
{
}

void Radios::startScreenAndBios() {
  ledMatrixInit();
  servoIndicatorsInit();

  display.begin();

  DcsBios::setup();

  activateNextModule();
}

void Radios::run() {
  DcsBios::loop();
}


void Radios::activateNextModule() {
  if (arc210.isActive) {
    activateUhf();
  } else if (uhf.isActive) {
    activateVhfFm();
  } else if (vhfFm.isActive) {
    activateIls();
  } else if (ils.isActive) {
    activateTacan();
  } else if (tacan.isActive) {
    activateIntercomPanel();
  } else if (intercomPanel.isActive) {
    activateCheckLists();
  } else if (checklists.isActive) {
    activateArc210();
  } else {
    activateArc210();
  }
}

void Radios::activatePreviousModule() {
  if (arc210.isActive) {
    activateCheckLists();
  } else if (uhf.isActive) {
    activateArc210();
  } else if (vhfFm.isActive) {
    activateUhf();
  } else if (ils.isActive) {
    activateVhfFm();
  } else if (tacan.isActive) {
    activateIls();
  } else if (intercomPanel.isActive) {
    activateTacan();
  } else if (checklists.isActive) {
    activateIntercomPanel();
  } else {
    activateArc210();
  }
}

int Radios::getActivatedModule() {
  return currentRadio;
}

void Radios::sendDcsCommand(const char* msg, const char* args) {
  while(!DcsBios::tryToSendDcsBiosMessage(msg, args));
}

unsigned int Radios::getArc210MasterMode() {
  return arc210.selectedMasterSwitch;
}
unsigned int Radios::getArc210SecondaryMode() {
  return arc210.selectedSecondarySwitch;
}

unsigned int Radios::getUHFMasterMode() {
  return uhf.selectedMasterSwitch;
}
unsigned int Radios::getUHFSecondaryMode() {
  return uhf.selectedSecondarySwitch;
}

void Radios::displayCheckListsTopScreenBtn() {
  checklists.onTopScreenBtn();
}
void Radios::displayCheckListsMiddleScreenBtn() {
  checklists.onMiddleScreenBtn();
}
void Radios::displayCheckListsBottomScreenBtn() {
  checklists.onBottomScreenBtn();
}
void Radios::displayCheckListsMenuBtn() {
  checklists.printMainMenu();
}

void Radios::displayCheckListsPage(int page) {
  checklists.onPageChange(page);
}
