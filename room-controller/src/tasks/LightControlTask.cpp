#include "LightControlTask.h"
#include "devices/Led.h"
#include "config.h"


LightControlTask::LightControlTask(SmartRoom* room) {
    this->room = room;
    this->light = room->getLight();
    //this->state = OFF;
    setStateOff();
}

void LightControlTask::tick() {
    switch (state) {
    case OFF: {
        if (room->isAutoMode()) {
            if (room->isPresenceDetected() && room->getLightLevel() < MIN_LIGHT_LEVEL) {
                setStateOn();
            }
        } else {
            if (!room->isAutoMode()) {
                setStateControlled();
            }
        }
        break;
    }

    case ON: {
        if (room->isAutoMode()) {
            if (!room->isPresenceDetected() || room->getLightLevel() >= MIN_LIGHT_LEVEL) {
                setStateOff();
            }
        } else {
            if (!room->isAutoMode()) {
                setStateControlled();
            }
        }
        break;
    }

    case MANUAL: {
        if (!room->isAutoMode()) {
            if (room->getRemoteLightValue() == true) {
                light->switchOn();
            } else {
                light->switchOff();
            }
        } else {
            if (room->isPresenceDetected() && room->getLightLevel() < MIN_LIGHT_LEVEL) {
                setStateOn();
            } else {
                setStateOff();
            }
        }
    }

    default: {
            break;
        }
    }
}

void LightControlTask::setStateOn() {
    state = ON;
    light->switchOn();
}

void LightControlTask::setStateOff() {
    state = OFF;
    light->switchOff();
}

void LightControlTask::setStateControlled() {
    state = MANUAL;
}
