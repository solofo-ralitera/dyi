#include "TftDisplay.h"
#include "Tacan.h"

#define SECONDARY_TACAN_SWITCH_OFFSET 230

Tacan::Tacan(TftDisplay* _display)
{
    display = _display;
}

void Tacan::activate() {
    if (isActive == false) {
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, SECONDARY_TACAN_SWITCH_OFFSET);
        display->printTRHelp("Ton", "vol.");
        display->printBCHelp("test");
        display->drawVolume(volume);
        display->drawRadioSql(tone);
    }
    isActive = true;
}

void Tacan::deactivate() {
    isActive = false;
}

void Tacan::setFrequency(char* newValue) {
    // if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Tacan::setSelectedMasterSwitch(unsigned int newValue) {
    // if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, SECONDARY_TACAN_SWITCH_OFFSET);
}

void Tacan::setVolume(int newValue) {
    volume = newValue;
    if (isActive) display->drawVolume(volume);
}

void Tacan::setTest(unsigned int newValue) {
    if (isActive) display->highLightBCHelp(newValue);
}

void Tacan::setTone(unsigned int newValue) {
    tone = newValue;
    if (isActive) display->drawRadioSql(tone);
}
