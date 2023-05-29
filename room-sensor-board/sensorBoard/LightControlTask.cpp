#include "LightControlTask.h"


LightControlTask::LightControlTask(RoomSensorBoard* sensorBoard) {
    this->sensorBoard = sensorBoard;
    this->lightState = OFF;
}

void LightControlTask::tick() {
    switch (lightState) {
    case OFF:
        if (sensorBoard->isPresenceDetected()) {
            setStateOn();
        }
        break;

    case ON:
        if (!sensorBoard->isPresenceDetected()) {
            setStateOff();
        }
        break;
    
    default:
        break;
    }
}

void LightControlTask::setStateOff() {
    lightState = OFF;
    sensorBoard->turnLightOff();
}

void LightControlTask::setStateOn() {
    lightState = ON;
    sensorBoard->turnLightOn();
}
