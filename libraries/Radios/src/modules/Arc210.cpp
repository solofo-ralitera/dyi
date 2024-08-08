// #include "DcsBios.h"
// #include "internal/Addresses.h"

#include "TftDisplay.h"
#include "Arc210.h"


Arc210::Arc210(TftDisplay* _display):
title ("VHF"),
numMasterSwitches (4),
masterSwitches {
    "OFF",
    "TR G",
    "TR",
    // "ADF",
    "CHG PRST",
    // "TEST",
    // "ZERO (PULL)",
},
numSecondarySwitches (4),
secondarySwitches {
    // "ECCM MASTER",
    // "ECCM",
    "PRST",
    "MAN",
    // "MAR",
    "243",
    "121 (PULL)",
}
{
    display = _display;
    channel = "xx";
    frequency = "XXXXXXX";
    modulation = "xx";

    selectedMasterSwitch = 0;
    selectedSecondarySwitch = 0;

    isActive = false;
}

void Arc210::begin() {
    /*
    Secondary switch
        0: ECCM MASTER
        1: ECCM
        2: PRST
        3: MAN
        4: MAR
        5: 243
        6: 121 (PULL)

    */
}

void Arc210::run() {
}

void Arc210::activate() {
    if (isActive == false) {
        display->printRadioChannel(channel);
        display->printRadioFrequency(frequency);
        display->printRadioModulation(modulation);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 250);
    }
    isActive = true;
}

void Arc210::deactivate() {
    isActive = false;
}


void Arc210::setChannel(char* newValue) {
    // !!! Switch
    //      A_10C_ARC210_ACTIVE_ECCM_CHANNEL
    //      A_10C_ARC210_ACTIVE_CHANNEL
    if (channel == newValue) return;
    channel = newValue;
    if (isActive) display->printRadioChannel(channel);
}

void Arc210::setFrequency(char* newValue) {
    if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Arc210::setModulation(char* newValue) {
    if (modulation == newValue) return;
    modulation = newValue;
    if (isActive) display->printRadioModulation(modulation);
}

void Arc210::setSelectedMasterSwitch(unsigned int newValue) {
    if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void Arc210::setSelectedSecondarySwitch(unsigned int newValue) {
    if (selectedSecondarySwitch == newValue) return;
    selectedSecondarySwitch = newValue;
    if (isActive) display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 250);
}
