#include "RoomSensorBoard.h"
#include "LightSensorImpl.h"
#include "Led.h"


RoomSensorBoard::RoomSensorBoard(int pirPin, int lightSensorPin, int lightPin) {
    this->pir = new Pir(pirPin);
    this->lightSensor = new LightSensorImpl(lightSensorPin);
    this->light = new Led(lightPin);

    this->pir->calibrate();
}

void RoomSensorBoard::samplePresence() {
    pir->detectPresence();
    presenceDetected = pir->isDetected();
}

void RoomSensorBoard::sampleLightLevel() {
    lightLevel = lightSensor->getLightLevel();
}

bool RoomSensorBoard::isPresenceDetected() {
    return presenceDetected;
}

double RoomSensorBoard::getLightLevel() {
    return lightLevel;
}

void RoomSensorBoard::turnLightOff() {
    light->switchOff();
}

void RoomSensorBoard::turnLightOn() {
    light->switchOn();
}
