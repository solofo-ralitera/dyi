#include "TftDisplay.h"
#include "Tacan.h"


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

void Tacan::begin() {
}

void Tacan::run() {
}

void Tacan::activate() {
    if (isActive == false) {
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 270);
    }
    isActive = true;
}

void Tacan::deactivate() {
    isActive = false;
}

void Tacan::setFrequency(char* newValue) {
    if (frequency == newValue) return;
    frequency = newValue;
    if (isActive) display->printRadioFrequency(frequency);
}

void Tacan::setSelectedMasterSwitch(unsigned int newValue) {
    if (selectedMasterSwitch == newValue) return;
    selectedMasterSwitch = newValue;
    if (isActive) display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 270);
}
