#include "TftDisplay.h"
#include "Ils.h"


Ils::Ils(TftDisplay* _display) {
    display = _display;
}

void Ils::activate() {
    if (isActive == false) {
        display->printRadioFrequency(frequency);
        display->printRadioSwitch(masterSwitches, numMasterSwitches, selectedMasterSwitch, 0);
        display->printTRHelp("Ton", "vol.");
        display->drawVolume(volume);
        display->drawRadioSql(tone);
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

void Ils::setTone(unsigned int newValue) {
    tone = newValue;
    if (isActive) display->drawRadioSql(tone);
}
