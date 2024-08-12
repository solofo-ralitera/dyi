// #include "DcsBios.h"
// #include "internal/Addresses.h"

#include "TftDisplay.h"
#include "Arc210.h"


#define SECONDARY_ARC210_SWITCH_OFFSET 220

Arc210::Arc210(TftDisplay* _display):
title ("VHF"),
numMasterSwitches (7),
masterSwitches {
    "OFF",
    "TR G",
    "TR",
    "ADF",
    "CHG PRST",
    "TEST",
    "ZERO",
},
numSecondarySwitches (7),
secondarySwitches {
    "ECCM MTR",
    "ECCM",
    "PRST",
    "MAN",
    "MAR",
    "243",
    "121",
}
{
    display = _display;
    channel = "xx";
    frequency = "XXXXXXX";
    modulation = "xx";
    sql = 0;
    selectedMasterSwitch = 0;
    selectedSecondarySwitch = 0;

    isActive = false;
}

void Arc210::activate() {
    if (isActive == false) {
        display->printRadioChannel(channel);
        display->printRadioFrequency(frequency);
        display->printRadioModulation(modulation);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, SECONDARY_ARC210_SWITCH_OFFSET);
        display->printTRHelp("sql", "-");
        display->drawRadioSql(sql);
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
    // if (channel == newValue) return;
    channel = newValue;
    if (isActive) display->printRadioChannel(channel);
}

void Arc210::setFrequency(char* newValue) {
    // if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Arc210::setModulation(char* newValue) {
    // if (modulation == newValue) return;
    modulation = newValue;
    if (isActive) display->printRadioModulation(modulation);
}

void Arc210::setSelectedMasterSwitch(unsigned int newValue) {
    // if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void Arc210::setSelectedSecondarySwitch(unsigned int newValue) {
    // if (selectedSecondarySwitch == newValue) return;
    selectedSecondarySwitch = newValue;
    if (isActive) display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, SECONDARY_ARC210_SWITCH_OFFSET);
}

void Arc210::setSql(unsigned int newValue) {
    sql = newValue;
    if (isActive) display->drawRadioSql(sql);
}
