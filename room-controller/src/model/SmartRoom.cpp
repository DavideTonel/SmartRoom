#include "SmartRoom.h"
#include "devices/Led.h"


SmartRoom::SmartRoom(int rollerblindServoPin, int lightPin) {
    this->rollerblind = new RollerBlind(rollerblindServoPin);
    this->light = new Led(lightPin);

    this->presenceDetected = false;
    this->lightLevel = 0;

    this->controlMode = AUTO;

    this->remoteBlindOpenPercentage = 0;
    this->remoteLightOn = false;
}

RollerBlind* SmartRoom::getRollerBlinds() {
    return this->rollerblind;
}

Light* SmartRoom::getLight() {
    return this->light;
}

bool SmartRoom::isPresenceDetected() {
    return this->presenceDetected;
}

double SmartRoom::getLightLevel() {
    return this->lightLevel;
}

void SmartRoom::setPresenceDetected(bool value) {
    if (this->presenceDetected != value) {
        this->presenceDetected = value;
    }
}

void SmartRoom::setLightLevel(double value) {
    if (this->lightLevel != value) {
        this->lightLevel = value;
    }
}

bool SmartRoom::isAutoMode() {
    return this->controlMode == AUTO;
}

bool SmartRoom::isSerialMode() {
    return this->controlMode == MANUAL_SERIAL;
}

bool SmartRoom::isBluetoothMode() {
    return this->controlMode == MANUAL_BT;
}

void SmartRoom::setAutoMode() {
    this->controlMode = AUTO;
}

void SmartRoom::setSerialMode() {
    this->remoteBlindOpenPercentage = this->getRollerBlinds()->getOpenPercentage();
    this->remoteLightOn = this-getLight()->isOn();
    this->controlMode = MANUAL_SERIAL;
}

void SmartRoom::setBluetoothMode() {
    this->remoteBlindOpenPercentage = this->getRollerBlinds()->getOpenPercentage();
    this->remoteLightOn = this-getLight()->isOn();
    this->controlMode = MANUAL_BT;
}

void SmartRoom::setRemoteBlindOpenPercentage(int value) {
    this->remoteBlindOpenPercentage = value;
}

int SmartRoom::getRemoteBlindOpenPercentage() {
    return this->remoteBlindOpenPercentage;
}

void SmartRoom::setRemoteLightValue(int value) {
    if (this->remoteLightOn != value) {
        this->remoteLightOn = value;
    }
}

bool SmartRoom::getRemoteLightValue() {
    return this->remoteLightOn;
}
