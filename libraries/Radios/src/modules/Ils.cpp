#include "TftDisplay.h"
#include "Ils.h"


Ils::Ils(TftDisplay* _display):
title ("ILS"),
numMasterSwitches (2),
masterSwitches {
    "OFF",
    "PWR",
}
{
    display = _display;
    frequency = "XXXXXX";

    selectedMasterSwitch = 0;
    volume = 0;
    isActive = false;
}

void Ils::activate() {
    if (isActive == false) {
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printTRHelp("-", "vol.");
        display->drawVolume(volume);
    }
    isActive = true;
}

void Ils::deactivate() {
    isActive = false;
}

void Ils::setFrequency(char* newValue) {
    // if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Ils::setSelectedMasterSwitch(unsigned int newValue) {
    // if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
}

void Ils::setVolume(int newValue) {
    volume = newValue;
    if (isActive) display->drawVolume(volume);
}