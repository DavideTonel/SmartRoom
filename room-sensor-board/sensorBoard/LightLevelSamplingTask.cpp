#include "LightLevelSamplingTask.h"


LightLevelSamplingTask::LightLevelSamplingTask(RoomSensorBoard* sensorBoard) {
    this->sensorBoard = sensorBoard;
}

void LightLevelSamplingTask::tick() {
    sensorBoard->sampleLightLevel();
}
