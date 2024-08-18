#include "TftDisplay.h"
#include "intercomPanel.h"

IntercomPanel::IntercomPanel(TftDisplay* _display) {
    display = _display;
}

void IntercomPanel::setSelectedSecondarySwitch(unsigned int newValue) {
    selectedSecondarySwitch = newValue;
    if (isActive) display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 280);
}

void IntercomPanel::drawInt(boolean unmuteChange, boolean volumChange) {
    if (unmuteChange) {
        display->printIntercomCircle(0, 20, intUnmute);
        display->printIntercomText("INT", 0, 20, intUnmute);
    }
    if (unmuteChange || volumChange) {
        display->printIntercomVolume(0, 20, intVolume, intUnmute);
    }
}

void IntercomPanel::drawAim(boolean unmuteChange, boolean volumChange) {
    if (unmuteChange) {
        display->printIntercomCircle(40, 70, aimUnmute);
        display->printIntercomText("AIM", 40, 70, aimUnmute);
    }
    if (unmuteChange || volumChange) {
        display->printIntercomVolume(40, 70, aimVolume, aimUnmute);
    }
}

void IntercomPanel::drawFm(boolean unmuteChange, boolean volumChange) {
    if (unmuteChange) {
        display->printIntercomCircle(150, 20, fmUnmute);
        display->printIntercomText("FM", 150, 20, fmUnmute);
    }
    if (unmuteChange || volumChange) {
        display->printIntercomVolume(150, 20, fmVolume, fmUnmute);
    }
}

void IntercomPanel::drawUhf(boolean unmuteChange, boolean volumChange) {
    if (unmuteChange) {
        display->printIntercomCircle(250, 20, uhfUnmute);
        display->printIntercomText("UHF", 250, 20, uhfUnmute);
    }
    if (unmuteChange || volumChange) {
        display->printIntercomVolume(250, 20, uhfVolume, uhfUnmute);
    }
}

void IntercomPanel::drawVhf(boolean unmuteChange, boolean volumChange) {
    if (unmuteChange) {
        display->printIntercomCircle(210, 70, vhfUnmute);
        display->printIntercomText("VHF", 210, 70, vhfUnmute);
    }
    if (unmuteChange || volumChange) {
        display->printIntercomVolume(210, 70, vhfVolume, vhfUnmute);
    }
}

void IntercomPanel::activate() {
    if (isActive == false) {
        drawInt(true, true);
        drawAim(true, true);
        drawFm(true, true);
        drawVhf(true, true);
        drawUhf(true, true);
        display->printTRHelp("-", "vol.");
        display->drawVolume(volume);
        display->printRadioSwitch(secondarySwitches, numSecondarySwitches, selectedSecondarySwitch, 280);
        display->printBCHelp(" HM ");
    }
    isActive = true;
}

void IntercomPanel::deactivate() {
    isActive = false;
}

void IntercomPanel::setVolume(unsigned int newValue) {
    volume = newValue;
    if (isActive) display->drawVolume(volume);
}

void IntercomPanel::setHm(unsigned int newValue) {
    if (isActive) display->highLightBCHelp(newValue);
}

void IntercomPanel::setIntUnmute(unsigned int newValue) {
    intUnmute = newValue;
    if (isActive) drawInt(true, false);
}

void IntercomPanel::setIntVolume(unsigned int newValue) {
    intVolume = newValue;
    if (isActive) drawInt(false, true);
}

void IntercomPanel::setAimUnmute(unsigned int newValue) {
    aimUnmute = newValue;
    if (isActive) drawAim(true, false);
}

void IntercomPanel::setAimVolume(unsigned int newValue) {
    aimVolume = newValue;
    if (isActive) drawAim(false, true);
}

void IntercomPanel::setFmUnmute(unsigned int newValue) {
    fmUnmute = newValue;
    if (isActive) drawFm(true, false);
}

void IntercomPanel::setFmVolume(unsigned int newValue) {
    fmVolume = newValue;
    if (isActive) drawFm(false, true);
}

void IntercomPanel::setUhfUnmute(unsigned int newValue) {
    uhfUnmute = newValue;
    if (isActive) drawUhf(true, false);
}

void IntercomPanel::setUhfVolume(unsigned int newValue) {
    uhfVolume = newValue;
    if (isActive) drawUhf(false, true);
}

void IntercomPanel::setVhfUnmute(unsigned int newValue) {
    vhfUnmute = newValue;
    if (isActive) drawVhf(true, false);
}

void IntercomPanel::setVhfVolume(unsigned int newValue) {
    vhfVolume = newValue;
    if (isActive) drawVhf(false, true);
}