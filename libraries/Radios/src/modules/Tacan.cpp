#include "TftDisplay.h"
#include "Tacan.h"

#define SECONDARY_TACAN_SWITCH_OFFSET 230

Tacan::Tacan(TftDisplay* _display):
title ("TACAN"),
numMasterSwitches (5),
masterSwitches {
    "OFF",
    "REC",
    "T/R",
    "A/A Rec",
    "A/A T/R",
}
{
    display = _display;
    frequency = "XXXX";

    selectedMasterSwitch = 0;

    isActive = false;
}

void Tacan::activate() {
    if (isActive == false) {
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, SECONDARY_TACAN_SWITCH_OFFSET);
        display->printTRHelp("-", "vol.");
        display->printBCHelp("test");
        display->drawVolume(volume);
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
    if (isActive) display->drawTacanTest(newValue);
}