// #include "DcsBios.h"
// #include "internal/Addresses.h"

#include "TftDisplay.h"
#include "Uhf.h"

#define SECONDARY_UHF_SWITCH_OFFSET 240

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

    selectedMasterSwitch = 0;
    selectedSecondarySwitch = 0;
    volume = 0;

    isActive = false;
}

void Uhf::activate() {
    if (isActive == false) {
        display->printRadioChannel(channel);
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, SECONDARY_UHF_SWITCH_OFFSET);
        display->printTRHelp("sql", "vol.");
        display->drawVolume(volume);
        display->drawRadioSql(sql);
    }
    isActive = true;
}

void Uhf::deactivate() {
    isActive = false;
}

void Uhf::setChannel(char* newValue) {
    // if (channel == newValue) return;
    channel = newValue;
    if (isActive) display->printRadioChannel(channel);
}

void Uhf::setFrequency(char* newValue) {
    // if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Uhf::setSelectedMasterSwitch(unsigned int newValue) {
    // if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void Uhf::setSelectedSecondarySwitch(unsigned int newValue) {
    // if (selectedSecondarySwitch == newValue) return;
    selectedSecondarySwitch = newValue;
    if (isActive) display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, SECONDARY_UHF_SWITCH_OFFSET);
}

void Uhf::setVolume(int newValue) {
    volume = newValue;
    if (isActive) display->drawVolume(volume);
}

void Uhf::setSql(unsigned int newValue) {
    sql = newValue;
    if (isActive) display->drawRadioSql(sql);
}
