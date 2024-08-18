// #include "DcsBios.h"
// #include "internal/Addresses.h"

#include "TftDisplay.h"
#include "Uhf.h"

#define SECONDARY_UHF_SWITCH_OFFSET 240

Uhf::Uhf(TftDisplay* _display) {
    display = _display;
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
    channel = newValue;
    if (isActive) display->printRadioChannel(channel);
}

void Uhf::setFrequency(char* newValue) {
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Uhf::setSelectedMasterSwitch(unsigned int newValue) {
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void Uhf::setSelectedSecondarySwitch(unsigned int newValue) {
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
