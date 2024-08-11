// #include "DcsBios.h"
// #include "internal/Addresses.h"

#include "TftDisplay.h"
#include "Uhf.h"


Uhf::Uhf(TftDisplay* _display):
title ("UHF"),
numMasterSwitches (4),
masterSwitches {
    "OFF",
    "MAIN",
    "BOTH",
    "ADF",
},
numSecondarySwitches (3),
secondarySwitches {
    "MNL",
    "PRESET",
    "GRD",
}
{
    display = _display;
    channel = "xx";
    frequency = "XXXXXXX";
    freq100MHz = "";

    selectedMasterSwitch = 0;
    selectedSecondarySwitch = 0;

    isActive = false;
}

void Uhf::begin() {
}

void Uhf::run() {
}

void Uhf::activate() {
    if (isActive == false) {
        display->printRadioChannel(channel);
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 280);
    }
    isActive = true;
}

void Uhf::deactivate() {
    isActive = false;
}


void Uhf::setChannel(char* newValue) {
    if (channel == newValue) return;
    channel = newValue;
    if (isActive) display->printRadioChannel(channel);
}

void Uhf::setFrequency(char* newValue) {
    if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Uhf::setSelectedMasterSwitch(unsigned int newValue) {
    if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void Uhf::setSelectedSecondarySwitch(unsigned int newValue) {
    if (selectedSecondarySwitch == newValue) return;
    selectedSecondarySwitch = newValue;
    if (isActive) display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 280);
}
