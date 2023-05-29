#include "PresenceSamplingTask.h"


PresenceSamplingTask::PresenceSamplingTask(RoomSensorBoard* sensorBoard) {
    this->sensorBoard = sensorBoard;
}

void PresenceSamplingTask::tick() {
    sensorBoard->samplePresence();
}
