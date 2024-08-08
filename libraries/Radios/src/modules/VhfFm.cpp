#include "TftDisplay.h"
#include "VhfFm.h"


VhfFm::VhfFm(TftDisplay* _display):
title ("VHF FM"),
numMasterSwitches (4),
masterSwitches {
    "FM",
    "AM",
    "MAN",
    "PRE",
},
numSecondarySwitches (3),
secondarySwitches {
    "OFF",
    "TR",
    "DF",
}
{
    display = _display;
    channel = "xx";
    frequency = "XXXXXXX";

    selectedMasterSwitch = 0;
    selectedSecondarySwitch = 0;

    isActive = false;
}

void VhfFm::begin() {
}

void VhfFm::run() {
}

void VhfFm::activate() {
    if (isActive == false) {
        display->printRadioChannel(channel);
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 280);
    }
    isActive = true;
}

void VhfFm::deactivate() {
    isActive = false;
}


void VhfFm::setChannel(char* newValue) {
    if (channel == newValue) return;
    channel = newValue;
    if (isActive) display->printRadioChannel(channel);
}

void VhfFm::setFrequency(char* newValue) {
    if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void VhfFm::setSelectedMasterSwitch(unsigned int newValue) {
    if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void VhfFm::setSelectedSecondarySwitch(unsigned int newValue) {
    if (selectedSecondarySwitch == newValue) return;
    selectedSecondarySwitch = newValue;
    if (isActive) display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 280);
}
